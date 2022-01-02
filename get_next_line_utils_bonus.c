/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:21:07 by ple-stra          #+#    #+#             */
/*   Updated: 2022/01/02 21:32:24 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strllen(char const *str, char c, size_t l)
{
	char	*str2;

	if (!str)
		return (0);
	str2 = (char *)str;
	l++;
	while (--l && *str != c)
		str++;
	if (l && *str == c && c != 0)
		return (str - str2 + 1);
	return (str - str2);
}

void	*free_all(t_lstring *l_line, char **sbuf)
{
	t_lstring	*to_free;

	free(*sbuf);
	*sbuf = 0;
	while (l_line)
	{
		to_free = l_line;
		l_line = l_line->previous;
		if (to_free->string)
			free(to_free->string);
		free(to_free);
	}
	return (NULL);
}
