/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:30 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/23 15:42:31 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
