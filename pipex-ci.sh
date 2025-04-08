#!/bin/bash
# pipex-ci.sh - CI test script for the pipex project

set -e  # Exit immediately if any command fails.
set -u  # Treat unset variables as an error.
set -o pipefail  # Exit if any command in a pipeline fails.

# Clean up previous builds and outputs
make fclean || true

echo "[cleaning pipex]"
echo "Building the project..."
make all

# Create temporary test directory
TEST_DIR="test_tmp"
mkdir -p "$TEST_DIR"
echo "Test directory: $TEST_DIR"
cd "$TEST_DIR"
mkdir -p inputs outputs expected

# ------------------------------------------------------------------------------
# Helper function to run a test and compare outputs
# ------------------------------------------------------------------------------
run_test() {
    local test_name="$1"
    local infile="$2"
    local cmd1="$3"
    local cmd2="$4"
    local outfile="outputs/${test_name}_out.txt"
    local expected_out="expected/${test_name}_expected.txt"

    echo "Running test: ${test_name}"

    # Generate expected output using shell redirection.
    # If the shell command fails, the error message "Error occurred generating expected output."
    # is appended to the expected file. We will filter that out before comparing.
    if ! < "$infile" $cmd1 | $cmd2 > "$expected_out" 2>&1; then
        echo "Error occurred generating expected output." >> "$expected_out"
    fi

    # Execute the pipex project. Adjust relative paths if necessary.
    echo "Executing: ./pipex $infile $cmd1 $cmd2 $outfile"
    ../pipex "$infile" "$cmd1" "$cmd2" "$outfile" 2>&1 || true

    # Filter out the extra error message from both expected and actual output.
    expected_filtered=$(grep -v "Error occurred generating expected output." "$expected_out" || true)
    actual_filtered=$(grep -v "Error occurred generating expected output." "$outfile" || true)

    # Compare filtered outputs.
    if diff -q <(echo "$expected_filtered") <(echo "$actual_filtered") > /dev/null; then
        echo "[PASS] ${test_name}"
    else
        echo "[FAIL] ${test_name}"
        echo "Expected output:"
        echo "$expected_filtered"
        echo "Actual output:"
        echo "$actual_filtered"
        exit 1
    fi
    echo
}

# ------------------------------------------------------------------------------
# Test Cases (Edge and Standard Cases)
# ------------------------------------------------------------------------------

# Test Case 1: Standard operation
echo "Test Case 1: Standard operation"
echo -e "line1\nline2\nline3" > inputs/infile1.txt
run_test "standard" "inputs/infile1.txt" "cat" "wc -l"

# Test Case 2: Command with arguments
echo "Test Case 2: Command with arguments"
echo -e "a1 a2\na3 a4" > inputs/infile2.txt
run_test "arguments" "inputs/infile2.txt" "grep a1" "wc -w"

# Test Case 3: Non-existent input file
echo "Test Case 3: Non-existent input file"
# Do not create inputs/no_such_file.txt so that it simulates a missing file.
run_test "missing_infile" "inputs/no_such_file.txt" "cat" "wc -l"

# Test Case 4: Invalid command
echo "Test Case 4: Invalid command"
echo -e "sample data" > inputs/infile3.txt
run_test "invalid_command" "inputs/infile3.txt" "nonexistentcmd" "wc -l"

# Test Case 5: Empty input file
echo "Test Case 5: Empty input file"
touch inputs/infile_empty.txt
run_test "empty_file" "inputs/infile_empty.txt" "cat" "wc -c"

# Test Case 6: File permission error
echo "Test Case 6: Permission error on input file"
echo -e "cannot read" > inputs/infile_no_perm.txt
chmod 000 inputs/infile_no_perm.txt
run_test "permission_error" "inputs/infile_no_perm.txt" "cat" "wc -l"
chmod 644 inputs/infile_no_perm.txt  # Reset permissions for cleanup

# Test Case 7: Complex command arguments
echo "Test Case 7: Complex command arguments"
echo -e "apple banana\ncherry date" > inputs/infile4.txt
run_test "complex_args" "inputs/infile4.txt" "grep 'banana'" "wc -w"

echo "All tests passed successfully!"

# Clean up temporary test directory
rm -rf "$TEST_DIR"
