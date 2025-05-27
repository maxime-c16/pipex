/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:41:55 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/27 13:17:14 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_cmd_struct(t_pipex *pipex, char **av)
{
	int	i;

	i = 0;
	pipex->cmd = (t_cmd *)malloc(sizeof(t_cmd) * pipex->nb_cmd);
	if (!pipex->cmd)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		ciao(EXIT_FAILURE);
	}
	ft_bzero(pipex->cmd, sizeof(t_cmd) * pipex->nb_cmd);
	pipex->cmd[0].redir = ft_strdup(av[1]);
	pipex->cmd[pipex->nb_cmd - 1].redir = ft_strdup(av[pipex->nb_cmd + 2]);
	while (i < pipex->nb_cmd)
	{
		pipex->cmd[i].cmd = ft_split(av[i + 2], ' ');
		if (!pipex->cmd[i].cmd)
		{
			ft_putstr_fd("Error: malloc failed\n", 2);
			ciao(EXIT_FAILURE);
		}
		if (i != 0 && i != pipex->nb_cmd - 1)
			pipex->cmd[i].redir = NULL;
		i++;
	}
}

static int	is_absolute_path(const char *cmd)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (1);
	return (0);
}

void	resolve_cmd_paths(int index)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (!pipex->cmd[index].cmd[0])
	{
		ft_putstr_fd("Pipex: Command not found\n", 2);
		ciao(127);
	}
	if (is_absolute_path(pipex->cmd[index].cmd[0]))
	{
		if (access(pipex->cmd[index].cmd[0], F_OK | X_OK) == 0)
			pipex->cmd[index].path = ft_strdup(pipex->cmd[index].cmd[0]);
		else
		{
			ft_putstr_fd("Pipex: ", 2);
			ft_putstr_fd(pipex->cmd[index].cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ciao(127);
		}
	}
	else
		access_path(index);
}

void	parsing(char **av, char **env)
{
	t_pipex	*pipex;

	pipex = _pipex();
	init_cmd_struct(pipex, av);
	find_path(env);
}

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
