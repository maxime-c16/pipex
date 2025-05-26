/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:40 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/26 16:16:43 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
		waitpid(pipex->pid[i], &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
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
