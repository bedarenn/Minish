/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:54:10 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/18 14:10:51 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "minishell.h"

void	sig_rl(int code);
void	sig_here_doc(int code);
void	sig_fork(int code);

void	set_readline_signal(void)
{
	signal(SIGINT, sig_rl);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_fork(void)
{
	signal(SIGINT, sig_fork);
	signal(SIGQUIT, sig_fork);
}

void	set_signal_here_doc(void)
{
	signal(SIGINT, sig_here_doc);
	signal(SIGQUIT, sig_here_doc);
}

void	set_signal_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}