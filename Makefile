FILES	=	pipex.c
SRC_DIR	=	srcs
SRCS	=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ_DIR	=	.objs
OBJS	=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

NAME	=	pipex
CC		=	gcc
CFLAGS	=	-g3 
DEBUG	=	-fsanitize=address
RM		=	/bin/rm -rf
LDFLAGS	=	 -Llibft -lft

all:		$(NAME)

$(NAME):	$(OBJS)
		$(MAKE) -C libft
		$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

debug:		$(OBJS)
		$(MAKE) -C libft
		$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
		$(MAKE) -C libft clean
		$(RM) $(OBJ_DIR)

fclean: clean
		$(MAKE) -C libft fclean
		$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
