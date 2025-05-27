/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:02:52 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/27 12:46:47 by macauchy         ###   ########.fr       */
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
	// pipex->save_in = dup(STDIN_FILENO);
	// pipex->save_out = dup(STDOUT_FILENO);
	pipex->nb_cmd = ac - 3;
	parsing(av, env);
	pipe_fd();
	ft_exec(env);
	ciao(EXIT_SUCCESS);
	return (0);
}
