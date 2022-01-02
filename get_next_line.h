/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:16:43 by ple-stra          #+#    #+#             */
/*   Updated: 2022/01/02 21:32:24 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_lstring
{
	char				*string;
	size_t				len;
	struct s_lstring	*previous;
}	t_lstring;

typedef struct s_buf
{
	int		fd;
	size_t	rlen;
	ssize_t	len;
}	t_buf;

char	*get_next_line(int fd);

size_t	ft_strllen(char const *str, char c, size_t l);
void	*free_all(t_lstring *l_line, char **sbuf);
int		fill_buff_with_sbuff(char **sbuf, char **buf);

#endif
