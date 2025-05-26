/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:58 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/26 15:30:32 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_input_redir(void)
{
	t_pipex	*pipex;

	pipex = _pipex();
	pipex->infd = open(pipex->cmd[0].redir, O_RDONLY, 0777);
	if (pipex->infd == -1)
	{
		ft_putstr_fd("Error: open failed\n", 2);
		close(STDIN_FILENO);
		close_fds();
		ciao();
	}
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
		pipex->outfd = open(pipex->cmd[pipex->nb_cmd - 1].redir,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfd == -1)
		{
			ft_putstr_fd("Error: open failed\n", 2);
			close(STDOUT_FILENO);
			close_fds();
			ciao();
		}
		dup2(pipex->outfd, STDOUT_FILENO);
		close(pipex->outfd);
	}
}
