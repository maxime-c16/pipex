/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:02:52 by macauchy          #+#    #+#             */
/*   Updated: 2025/04/03 13:26:03 by macauchy         ###   ########.fr       */
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
			break;
		}
	}
	if (!pipex->path)
	{
		ft_putstr_fd("Error: PATH not found\n", 2);
		exit(1);
	}
}

void	parsing(char **av, char **env)
{
	t_pipex	*pipex;
	int		i;

	pipex = _pipex();
	pipex->cmd[0].cmd = ft_split(av[2], ' ');
	pipex->cmd[1].cmd = ft_split(av[3], ' ');
	if (!pipex->cmd[0].cmd || !pipex->cmd[1].cmd)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	pipex->cmd[0].redir = av[1];
	pipex->cmd[1].redir = av[4];
	find_path(env);
	// debug output
	dprintf(2, "cmd[0]: %s\n", pipex->cmd[0].cmd[0]);
	dprintf(2, "cmd[1]: %s\n", pipex->cmd[1].cmd[0]);
	dprintf(2, "redir[0]: %s\n", pipex->cmd[0].redir);
	dprintf(2, "redir[1]: %s\n", pipex->cmd[1].redir);
}

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
	
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	parsing(av, env);
	return (0);
}
