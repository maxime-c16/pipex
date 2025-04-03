/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:02:57 by macauchy          #+#    #+#             */
/*   Updated: 2025/04/03 13:12:05 by macauchy         ###   ########.fr       */
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
	int				fd[2];
	int				pid[2];
	struct s_cmd	cmd[2];
	char			**env;
	char			**path;
}					t_pipex;

t_pipex	*_pipex(void);

#endif
