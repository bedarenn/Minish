/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:06:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 14:47:21 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

t_list	*add_pid(t_list **list, pid_t pid)
{
	pid_t	*ptr;
	t_list	*new;

	ptr = malloc(sizeof(pid_t));
	*ptr = pid;
	new = wati_lstnew(ptr);
	wati_lstadd_back(list, new);
	return (*list);
}

t_bool	wait_pids(t_list *list)
{
	pid_t	*ptr;
	int		r;

	if (!list)
		return (TRUE);
	ptr = list->content;
	if (list->next)
		wait_pids(list->next);
	waitpid(*ptr, &r, 0);
	if (WIFEXITED(r))
		error_code = WEXITSTATUS(r);
	else
		error_code = 0;
	free(ptr);
	free(list);
	if (error_code > 0)
		return (FALSE);
	return (TRUE);
}
