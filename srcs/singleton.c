/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:11:00 by macauchy          #+#    #+#             */
/*   Updated: 2025/04/03 13:11:58 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_pipex	*_pipex(void)
{
	static t_pipex	pipex;
	static int		init = 0;

	if (!init)
	{
		ft_bzero(&pipex, sizeof(t_pipex));
		init = 1;
	}
	return (&pipex);
}
