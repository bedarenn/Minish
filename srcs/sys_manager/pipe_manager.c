/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:07:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 12:52:00 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

void	swap_spipe(t_pipe *fd)
{
	wati_close(fd->in);
	wati_close(fd->pipe[1]);
	fd->in = fd->pipe[0];
	fd->pipe[0] = -1;
	fd->pipe[1] = -1;
}
