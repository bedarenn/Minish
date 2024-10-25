/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:39:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/20 17:43:35 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*modify_token(char *line, t_list *env_lst)
{
	char	*start;
	char	*end;
	char	*tmp;
	int		dollar_count;

	dollar_count = count_dollars(line);
	while (dollar_count)
	{
		start = start_to_dollar(line, count_dollars(line) - dollar_count);
		tmp = dollar_to_dollar(line, count_dollars(line) - dollar_count);
		end = find_variable(env_lst, tmp);
		free(tmp);
		tmp = wati_strjoin(start, end);
		free(end);
		free(start);
		start = tmp;
		end = dollar_to_end(line, count_dollars(line) - dollar_count);
		tmp = wati_strjoin(start, end);
		free(start);
		free(end);
		free(line);
		line = tmp;
		dollar_count--;
	}
	return (remove_quote(line));
}

char	*verify_token(char *line, t_list *env_lst)
{
	if (!line)
		return (NULL);
	return (modify_token(line, env_lst));
}

void	free_list(t_list *lst)
{
	t_token	*token;
	t_list	*lst0;

	lst0 = lst;
	while (lst)
	{
		token = lst->content;
		free(token->str);
		lst = lst->next;
	}
	wati_lstclear(&lst0, free);
}

char	*convert_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= '\t' && line[i] <= 13)
			line[i] = ' ';
		i++;
	}
	return (line);
}

t_list	*init_parsing(t_string line)
{
	t_string	str;
	t_token		*token;
	t_list		*lst;
	t_test		test;

	lst = NULL;
	test.quote = false;
	while (wati_isspace(*line))
		line++;
	line = convert_space(line);
	while (*line)
	{
		str = get_next_token(&line, &test);
		if (!str)
			break ;
		token = new_token(str);
		wati_lstadd_back(&lst, wati_lstnew(token));
	}
	if (test.quote)
	{
		free_list(lst);
		wati_putstr_fd("error: missing quote\n", 2);
		return (NULL);
	}
	return (lst);
}
