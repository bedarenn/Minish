/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:39:27 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/30 19:46:40 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

static t_bool	_wati_exec(t_btree *node, t_shell *shell);

t_bool	wati_exec(t_shell shell)
{
	return (_wati_exec(shell.root, &shell));
}

static t_bool	_wati_exec(t_btree *node, t_shell *shell)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = node->item;
	if (cmd->oper == PIPE)
		wati_pipe(node, shell);
	else if (cmd->oper == NO)
	{
		pid = wati_execve(cmd, shell);
		waitpid(pid, NULL, 0);
	}
	return (TRUE);
}
