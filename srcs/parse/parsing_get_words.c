/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:31:32 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/26 15:32:16 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_operator(char **line)
{
	char	*str0;
	char	*str;
	int		len;

	str = *line;
	if (!is_char_operator(*str))
		return (NULL);
	str0 = str;
	while (*str == *str0)
		str++;
	len = str - str0;
	*line += len;
	return (wati_substr(str0, 0, len));
}

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
	while (*str && !is_char_operator(*str))
	{
		if ((*str == '"' || *str == 39) && !quote_c)
		{
			quote_c = *str;
			test->quote = !test->quote;
		}
		else if (quote_c && *str == quote_c)
			test->quote = !test->quote;
		else if (quote_c && *str == ' ' && !test->quote)
			break ;
		else if (!quote_c && *str == ' ')
			break ;
		str++;
	}
	*line += str - str0;
	return (wati_substr(str0, 0, str - str0));
}

char	*get_next_token(char **line, t_test *test)
{
	char	*token;

	token = get_operator(line);
	if (!token)
		token = get_word(line, test);
	if (test->quote)
		return (NULL);
	if (!token)
		return (NULL);
	skip_space(line);
	return (token);
}