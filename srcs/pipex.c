/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:02:52 by macauchy          #+#    #+#             */
/*   Updated: 2025/04/08 13:06:49 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	find_path(char **env)
{
	t_pipex	*pipex;
	int		i;

	i = -1;
	pipex = _pipex();
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pipex->path = ft_split(env[i] + 5, ':');
			if (!pipex->path)
			{
				ft_putstr_fd("Error: malloc failed\n", 2);
				exit(1);
			}
			break;
		}
	}
	if (!pipex->path)
	{
		ft_putstr_fd("Error: PATH not found\n", 2);
		exit(1);
	}
}

char	*cat_path_cmd(char *path, char *cmd)
{
	char	*res;
	char	*tmp;

	res = ft_strjoin(path, "/");
	tmp = res;
	res = ft_strjoin(res, cmd);
	free(tmp);
	return (res);
}

void	access_path(int index)
{
	t_pipex	*pipex;
	int		i;
	char	*tmp;

	i = 0;
	pipex = _pipex();
	while (pipex->path[i])
	{
		tmp = cat_path_cmd(pipex->path[i], pipex->cmd[index].cmd[0]);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			pipex->cmd[index].path = ft_strdup(tmp);
			free(tmp);
			break;
		}
		free(tmp);
		i++;
	}
	if (!pipex->cmd[index].path)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		ciao();
	}
}

void	parsing(char **av, char **env)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = _pipex();
	pipex->cmd[0].cmd = ft_split(av[2], ' ');
	pipex->cmd[1].cmd = ft_split(av[3], ' ');
	if (!pipex->cmd[0].cmd || !pipex->cmd[1].cmd)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	pipex->cmd[0].redir = ft_strdup(av[1]);
	pipex->cmd[1].redir = ft_strdup(av[4]);
	find_path(env);
	while (i < pipex->nb_cmd)
	{
		access_path(i);
		i++;
	}
}

void	pipe_fd(void)
{
	t_pipex	*pipex;
	int		i;

	pipex = _pipex();
	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipe(pipex->fd + (i * 2)) == -1)
		{
			ft_putstr_fd("Error: pipe failed\n", 2);
			ciao();
		}
		i++;
	}
}

void	ciao(void)
{
	t_pipex	*pipex;
	int		i;

	i = -1;
	pipex = _pipex();
	while (pipex->path[++i])
	{
		free(pipex->path[i]);
		pipex->path[i] = NULL;
	}
	free(pipex->path);
	close(pipex->save_in);
	close(pipex->save_out);
	exit(0);
}

void	close_fds(void)
{
	t_pipex	*pipex;
	int		i;

	pipex = _pipex();
	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		close(pipex->fd[i * 2]);
		close(pipex->fd[i * 2 + 1]);
		i++;
	}
}

void	duplicate_fds(int i)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (i == 0)
		dup2(pipex->fd[1], STDOUT_FILENO);
	else if (i == pipex->nb_cmd - 1)
		dup2(pipex->fd[i * 2 - 2], STDIN_FILENO);
	else
	{
		dup2(pipex->fd[i * 2 - 2], STDIN_FILENO);
		dup2(pipex->fd[i * 2 + 1], STDOUT_FILENO);
	}
	close_fds();
}

void	exec_redir(int i)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (i == 0)
	{
		pipex->infd = open(pipex->cmd[0].redir, O_RDONLY);
		if (pipex->infd == -1)
		{
			ft_putstr_fd("Error: open failed\n", 2);
			close(STDIN_FILENO);
			ciao();
		}
		dup2(pipex->infd, STDIN_FILENO);
		close(pipex->infd);
	}
	else if (i == pipex->nb_cmd - 1)
	{
		pipex->outfd = open(pipex->cmd[1].redir,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfd == -1)
		{
			ft_putstr_fd("Error: open failed\n", 2);
			close(STDOUT_FILENO);
			ciao();
		}
		dup2(pipex->outfd, STDOUT_FILENO);
		close(pipex->outfd);
	}
}

void	ft_exec_pipe(int i)
{
	t_pipex	*pipex;

	pipex = _pipex();
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		ciao();
	}
	if (pipex->pid[i] == 0)
	{
		duplicate_fds(i);
		exec_redir(i);
		if (execve(pipex->cmd[i].path, pipex->cmd[i].cmd, pipex->env) == -1)
		{
			ft_putstr_fd("Error: execve failed\n", 2);
			ciao();
		}
	}
}

void	ft_waitpid(void)
{
	t_pipex	*pipex;
	int		i;
	int		status;

	i = -1;
	pipex = _pipex();
	while (++i < pipex->nb_cmd)
	{
		waitpid(pipex->pid[i], &status, 0);
	}
	ft_putstr_fd("All child processes exited successfully\n", 2);
}

void	ft_exec(void)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = _pipex();
	while (i < pipex->nb_cmd)
	{
		ft_exec_pipe(i);
		i++;
	}
	close_fds();
	ft_waitpid();
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	pipex->save_in = dup(STDIN_FILENO);
	pipex->save_out = dup(STDOUT_FILENO);
	pipex->nb_cmd = ac - 3;
	parsing(av, env);
	pipe_fd();
	ft_exec();
	ciao();
	return (0);
}
