/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_root.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:31:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/05 14:32:01 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libwati.h"

t_btree	*new_root(t_btree **root, t_btree *node)
{
	node->left = *root;
	*root = node;
	return (*root);
}

t_btree	*add_root(t_btree **root, t_btree *node)
{
	if (!node)
		return (*root);
	if (*root)
		(*root)->right = node;
	else
		*root = node;
	return (*root);
}