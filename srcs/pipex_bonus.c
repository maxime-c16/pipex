/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:32:20 by macauchy          #+#    #+#             */
/*   Updated: 2025/06/02 11:32:23 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	pipex = _pipex();
	if (ac < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		return (1);
	}
	pipex->nb_cmd = ac - 3;
	parsing(av, env);
	pipe_fd();
	ft_exec(env);
	ciao(EXIT_SUCCESS);
	return (0);
}
