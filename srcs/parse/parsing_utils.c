/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:40:47 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/12 20:42:50 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_args(char **argv)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 1;
	tmp = NULL;
	result = wati_strdup(argv[1]);
	while (argv[i])
	{
		if (argv[i + 1])
		{
			tmp = result;
			result = wati_strjoin(tmp, " ");
			free(tmp);
			tmp = result;
			result = wati_strjoin(tmp, argv[i + 1]);
			free(tmp);
		}
		i++;
	}
	return (result);
}

void	print(void *str)
{
	wati_putendl_fd(str, 1);
}

int	is_char_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}