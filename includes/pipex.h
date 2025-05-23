/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:02:57 by macauchy          #+#    #+#             */
/*   Updated: 2025/05/23 15:39:19 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	*redir;
}			t_cmd;

typedef struct s_pipex
{
	int				nb_cmd;
	int				infd;
	int				outfd;
	int				fd[4];
	int				pid[2];
	struct s_cmd	cmd[2];
	int				save_in;
	int				save_out;
	char			**env;
	char			**path;
}					t_pipex;

t_pipex	*_pipex(void);
void	ciao(void);
void	find_path(char **env);
char	*cat_path_cmd(char *path, char *cmd);
void	access_path(int index);
void	parsing(char **av, char **env);
void	pipe_fd(void);
void	close_fds(void);
void	duplicate_fds(int i);
void	exec_input_redir(void);
void	exec_redir(int i);
void	ft_exec_pipe(int i);
void	ft_waitpid(void);
void	ft_exec(void);

#endif
