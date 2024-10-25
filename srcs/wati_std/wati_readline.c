/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:02:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/18 14:24:10 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

static char	*_wati_readline(t_list *env);

char	*wati_readline(t_list *env)
{
	t_string	str;

	set_readline_signal();
	str = _wati_readline(env);
	while (str != NULL && *str == '\0')
	{
		free(str);
		str = _wati_readline(env);
	}
	return (str);
}

static char	*_wati_readline(t_list *env)
{
	char	*prompt;
	char	*line;

	prompt = wati_prompt(env);
	if (prompt)
		line = readline(prompt);
	else
		line = readline("Minishell>");
	free(prompt);
	return (line);
}
