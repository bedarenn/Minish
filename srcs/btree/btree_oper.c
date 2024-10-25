/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:57:07 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/19 17:37:02 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"

t_bool	_btree_build_oper(t_btree **root, t_list **list)
{
	t_token	*token;

	if (!*list)
		return (TRUE);
	token = (*list)->content;
	if (token->oper == AND || token->oper == OR)
	{
		if (!btree_oper(root, list))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	btree_oper(t_btree **root, t_list **list)
{
	t_token	*token;
	t_btree	*new;
	t_cmd	*cmd;

	if (!(*list)->next || !is_opercmd(get_token((*list)->next)->oper) || !*root)
		return (wati_error(2, "parse error near '%s'", get_token(*list)->str));
	token = (*list)->content;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (wati_error(3, "alloc fail"));
	free(token->str);
	cmd->oper = token->oper;
	cmd->strs = NULL;
	cmd->files = NULL;
	new = btree_create_node(cmd);
	if (!new)
	{
		free(cmd);
		return (wati_error(3, "alloc fail"));
	}
	new_root(root, new);
	(*root)->right = NULL;
	(*list) = (*list)->next;
	return (TRUE);
}
