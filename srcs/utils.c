/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:28 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/23 15:43:35 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
