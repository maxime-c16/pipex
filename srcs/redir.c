/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:58 by macauchy          #+#    #+#             */
/*   Updated: 2025/06/02 12:34:48 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	open_input_redir(t_pipex *pipex)
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

static void	check_pipe_fd(t_pipex *pipex, int index)
{
	if (pipex->fd[(index - 1) * 2 + 1] == -1)
	{
		ft_putstr_fd("Pipex: Pipe failed\n", 2);
		close_fds();
		ciao(1);
	}
}

static void	open_output_redir(t_pipex *pipex)
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

void	open_redir(int index)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (index == 0 && pipex->cmd[0].redir)
		open_input_redir(pipex);
	else if (index > 0 && index < pipex->nb_cmd - 1)
		check_pipe_fd(pipex, index);
	else if (index == pipex->nb_cmd - 1)
		open_output_redir(pipex);
}

void	exec_redir(int i)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (i == 0)
	{
		dup2(pipex->infd, STDIN_FILENO);
		close(pipex->infd);
	}
	else if (i == pipex->nb_cmd - 1)
	{
		dup2(pipex->outfd, STDOUT_FILENO);
		close(pipex->outfd);
	}
}
