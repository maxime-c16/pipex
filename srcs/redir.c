/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:58 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/27 13:34:48 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	open_redir(int index)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (index == 0)
	{
		pipex->infd = open(pipex->cmd[0].redir, O_RDONLY);
		if (pipex->infd == -1)
		{
			ft_putstr_fd("Pipex: ", 2);
			ft_putstr_fd(pipex->cmd[0].redir, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			close_fds();
			ciao(1);
		}
	}
	else if (index == pipex->nb_cmd - 1)
	{
		pipex->outfd = open(pipex->cmd[pipex->nb_cmd - 1].redir,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfd == -1)
		{
			ft_putstr_fd("Pipex: ", 2);
			ft_putstr_fd(pipex->cmd[pipex->nb_cmd - 1].redir, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			close_fds();
			ciao(1);
		}
	}
}

void	exec_input_redir(void)
{
	t_pipex	*pipex;

	pipex = _pipex();
	dup2(pipex->infd, STDIN_FILENO);
	close(pipex->infd);
}

void	exec_redir(int i)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (i == 0)
		exec_input_redir();
	else if (i == pipex->nb_cmd - 1)
	{
		dup2(pipex->outfd, STDOUT_FILENO);
		close(pipex->outfd);
	}
}
