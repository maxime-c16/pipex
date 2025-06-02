/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:28 by macauchy          #+#    #+#             */
/*   Updated: 2025/06/02 12:23:40 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_cmd_structs(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		if (pipex->cmd[i].cmd)
		{
			free_tab(pipex->cmd[i].cmd);
			pipex->cmd[i].cmd = NULL;
		}
		if (pipex->cmd[i].redir)
		{
			free(pipex->cmd[i].redir);
			pipex->cmd[i].redir = NULL;
		}
		if (pipex->cmd[i].path)
		{
			free(pipex->cmd[i].path);
			pipex->cmd[i].path = NULL;
		}
		i++;
	}
}

static void	free_pipex_resources(t_pipex *pipex)
{
	free_tab(pipex->path);
	free_cmd_structs(pipex);
	free(pipex->cmd);
	free(pipex->fd);
	free(pipex->pid);
	if (pipex->infd != -1)
		close(pipex->infd);
	if (pipex->outfd != -1)
		close(pipex->outfd);
}

void	ciao(int status)
{
	t_pipex	*pipex;

	pipex = _pipex();
	free_pipex_resources(pipex);
	exit(status);
}
