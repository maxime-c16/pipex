/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:18:24 by macauchy          #+#    #+#             */
/*   Updated: 2025/06/02 12:18:33 by macauchy         ###   ########.fr       */
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
			break ;
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
			break ;
		}
		free(tmp);
		i++;
	}
	if (!pipex->cmd[index].path)
	{
		ft_putstr_fd("Pipex: ", 2);
		ft_putstr_fd(pipex->cmd[index].cmd[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		ciao(127);
	}
}
