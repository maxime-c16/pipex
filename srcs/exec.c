/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:40 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/27 16:08:56 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec_pipe(int i, char **env)
{
	t_pipex	*pipex;

	pipex = _pipex();
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		ciao(EXIT_FAILURE);
	}
	if (pipex->pid[i] == 0)
	{
		open_redir(i);
		resolve_cmd_paths(i);
		exec_redir(i);
		duplicate_fds(i);
		if (execve(pipex->cmd[i].path, pipex->cmd[i].cmd, env) == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(pipex->cmd[i].cmd[0], 2);
			ft_putstr_fd(": Command not found\n", 2);
			ciao(127);
		}
	}
}

void	ft_waitpid(void)
{
	t_pipex	*pipex;
	int		i;
	int		status;
	int		last_status;

	i = -1;
	status = 0;
	last_status = 0;
	pipex = _pipex();
	while (++i < pipex->nb_cmd)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (i == pipex->nb_cmd - 1)
			last_status = status;
	}
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(last_status))
		ciao(WEXITSTATUS(last_status));
}

static void	write_forked(void)
{
	t_pipex	*pipex;
	char	*line;

	pipex = _pipex();
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break;
		// Remove trailing newline if present
		size_t len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, pipex->cmd[0].limiter) == 0)
		{
			free(line);
			break ;
		}
		line[len - 1] = '\n'; // Restore newline for writing
		ft_putstr_fd(line, pipex->cmd[0].heredoc_fd);
		free(line);
	}
	close(pipex->cmd[0].heredoc_fd);
	unlink("heredoc_tmp");
}

static void	write_hd(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Pipex: fork failed\n", 2);
		ciao(1);
	}
	if (pid == 0)
	{
		write_forked();
		close(_pipex()->cmd[0].heredoc_fd);
	}
	else
		waitpid(pid, NULL, 0);
}


static void	open_heredoc(void)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (pipex->cmd[0].limiter)
	{
		pipex->cmd[0].heredoc_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->cmd[0].heredoc_fd == -1)
		{
			ft_putstr_fd("Pipex: heredoc_tmp: Permission denied\n", 2);
			ciao(1);
		}
		write_hd();
	}
}

void	ft_exec(char **env)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = _pipex();
	open_heredoc();
	while (i < pipex->nb_cmd)
	{
		ft_exec_pipe(i, env);
		i++;
	}
	close_fds();
	ft_waitpid();
}
