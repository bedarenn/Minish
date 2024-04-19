/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:31:32 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/19 12:56:23 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_space(char **line)
{
	char	*str0;
	char	*str;
	size_t	len;

	str0 = *line;
	str = str0;
	while (*str && *str == ' ')
		str++;
	len = str - str0;
	*line += len;
	return (str0);
}

char	*get_word(char **line, t_test *test)
{
	char	*str0;
	char	*str;
	char	quote_c;

	str = *line;
	str0 = str;
	quote_c = 0;
	while (*str && is_operator(str) == NO)
	{
		if ((*str == '"' || *str == 39) && !quote_c && !test->quote)
		{
			quote_c = *str;
			test->quote = !test->quote;
		}
		else if (quote_c && *str == quote_c)
		{
			quote_c = 0;
			test->quote = !test->quote;
		}
		else if ((!quote_c || (quote_c && !test->quote)) && *str == ' ')
			break ;
		str++;
	}
	*line += str - str0;
	return (wati_substr(str0, 0, str - str0));
}

char	*get_next_token(char **line, t_test *test)
{
	char	*token;

	token = get_operator(*line);
	if (!token)
		token = get_word(line, test);
	else
		*line += wati_strlen(token);
	if (test->quote)
	{
		free(token);
		return (NULL);
	}
	if (!token)
		return (NULL);
	skip_space(line);
	return (token);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_list	*lst;
	t_btree	*root;
	t_list	*env;

	env = env_getlist(envp);
	set_readline_signal();
	while (1)
	{
		str = wati_readline(env, argv[0]);
		add_history(str);
		while (str != NULL && *str == '\0')
		{
			free(str);
			str = wati_readline(env, argv[0]);
		}
		if (str == NULL)
			break ;
		lst = init_parsing(str, env);
		wati_lstiter(lst, print);
		wati_lstclear(&lst, free);
	}
	wati_lstclear(&env, free);
	return (0);
}
