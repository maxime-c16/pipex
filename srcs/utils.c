/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:28 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/26 10:51:27 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	ciao(void)
{
	t_pipex	*pipex;
	int		i;

	i = -1;
	pipex = _pipex();
	free_tab(pipex->path);
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
	free(pipex->cmd);
	free(pipex->env);
	free(pipex->fd);
	free(pipex->pid);
	close(pipex->save_in);
	close(pipex->save_out);
	exit(0);
}
