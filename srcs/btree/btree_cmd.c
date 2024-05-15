/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:58:14 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/15 12:44:28 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>

static t_bool	_btree_cmd(t_cmd *cmd, t_list **list, t_shell *shell);

t_bool	btree_cmd(t_btree **node, t_list **list, t_shell *shell)
{
	t_cmd	*cmd;

	if (get_token(*list)->oper == P_IN)
		return (btree_par(node, list, shell));
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		free(cmd);
		return (FALSE);
	}
	cmd->oper = NO;
	cmd->files = NULL;
	if (!_btree_cmd(cmd, list, shell))
	{
		free(cmd);
		return (FALSE);
	}
	*node = btree_create_node(cmd);
	if (!*node)
	{
		free_cmd(cmd);
		return (wati_error("alloc fail"));
	}
	return (TRUE);
}

static t_bool	cmd_parse_token(t_cmd *cmd, t_list **list, t_list **new,
					t_shell *shell);

static t_bool	_btree_cmd(t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_list		*lst;
	t_list		*new;

	lst = NULL;
	while (*list && is_opercmd(get_token(*list)->oper))
	{
		if (!cmd_parse_token(cmd, list, &new, shell))
		{
			wati_lstclear(&lst, free);
			return (FALSE);
		}
		if (new)
			wati_lstadd_back(&lst, new);
		(*list) = (*list)->next;
	}
	cmd->strs = lst;
	return (TRUE);
}

static t_bool	cmd_parse_redirect(t_cmd *cmd, t_list **list, t_shell *shell);

static t_bool	cmd_parse_token(t_cmd *cmd, t_list **list, t_list **new,
					t_shell *shell)
{
	t_token	*token;

	token = (*list)->content;
	*new = NULL;
	if (token->oper == NO)
	{
		*new = wati_lstnew(token->str);
		if (!*new)
			return (wati_error("alloc fail"));
		return (TRUE);
	}
	return (cmd_parse_redirect(cmd, list, shell));
}

static t_bool	cmd_parse_redirect(t_cmd *cmd, t_list **list, t_shell *shell)
{
	t_token	*token;
	t_token	*name;

	if (!(*list)->next || !(*list)->next->content)
		return (wati_error("no file given"));
	token = (*list)->content;
	free(token->str);
	(*list) = (*list)->next;
	name = (*list)->content;
	if (name->oper != NO)
		wati_error("syntax error near unexpected token '%s'", token->str);
	else if (token->oper == R_IN)
		return (add_file(&cmd->files, token->oper, name->str));
	else if (token->oper == R_OUT)
		return (add_file(&cmd->files, token->oper, name->str));
	else if (token->oper == H_IN)
	{
		(void)shell;
		return (add_fd(&cmd->files, token->oper, here_doc(name->str, shell)));
	}
	else if (token->oper == H_OUT)
		return (add_file(&cmd->files, token->oper, name->str));
	return (FALSE);
}

t_bool	is_opercmd(t_oper oper)
{
	return (oper == NO
		|| oper == H_IN
		|| oper == H_OUT
		|| oper == R_IN
		|| oper == R_OUT
		|| oper == P_IN);
}
