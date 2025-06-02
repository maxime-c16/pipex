/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:40 by macauchy          #+#    #+#             */
/*   Updated: 2025/06/02 12:24:28 by macauchy         ###   ########.fr       */
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

void	ft_exec(char **env)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = _pipex();
	while (i < pipex->nb_cmd)
	{
		ft_exec_pipe(i, env);
		i++;
	}
	close_fds();
	ft_waitpid();
}
