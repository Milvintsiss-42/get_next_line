/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:17:02 by ple-stra          #+#    #+#             */
/*   Updated: 2022/01/02 21:32:24 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(t_lstring *l_line, size_t line_len, char **sbuf)
{
	char		*line;
	t_lstring	*to_free;
	char		*str;

	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (free_all(l_line, sbuf));
	line += line_len;
	*line-- = 0;
	while (l_line)
	{
		str = l_line->string + l_line->len;
		while (l_line->len--)
			*line-- = *--str;
		to_free = l_line;
		l_line = l_line->previous;
		free(to_free->string);
		free(to_free);
	}
	return (line + 1);
}

t_lstring	*add_to_list(
	t_lstring *l_line,
	size_t real_len,
	char **sbuf
	)
{
	t_lstring	*new;
	char		*buf;
	char		*str;

	if (real_len == 0)
		return (l_line);
	new = malloc(sizeof(t_lstring));
	if (!new)
		return (free_all(l_line, sbuf));
	new->len = real_len;
	new->previous = l_line;
	new->string = malloc(sizeof(char) * (real_len));
	if (!new->string)
		return (free_all(new, sbuf));
	buf = *sbuf;
	str = new->string;
	while (real_len--)
		*str++ = *buf++;
	return (new);
}

void	save(
	char **sbuf,
	char *to_save,
	size_t len
	)
{
	char	*str;

	str = *sbuf;
	while (len--)
		*str++ = *to_save++;
	if (str - *sbuf <= BUFFER_SIZE)
		*str = 0;
}

int	loop(
	t_lstring **l_line,
	size_t *line_len,
	char **sbuf,
	t_buf *buf
	)
{
	while (1)
	{
		if (buf->rlen || buf->len)
		{
			*line_len += buf->rlen;
			*l_line = add_to_list(*l_line, buf->rlen, sbuf);
			if (!*l_line)
				return (0);
			if (buf->len - buf->rlen > 0
				|| (buf->rlen > 0 && *(*sbuf + buf->rlen - 1) == '\n'))
				break ;
		}
		buf->len = read(buf->fd, *sbuf, BUFFER_SIZE);
		if (buf->len <= 0)
			break ;
		buf->rlen = ft_strllen(*sbuf, '\n', buf->len);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	t_lstring		*l_line;
	static char		*sbuf[10240];
	t_buf			buf;
	size_t			line_len;

	if (!sbuf[fd])
	{
		sbuf[fd] = malloc(sizeof(char) * BUFFER_SIZE);
		*sbuf[fd] = 0;
		if (!sbuf[fd])
			return (NULL);
	}
	line_len = 0;
	l_line = NULL;
	buf.len = ft_strllen(sbuf[fd], 0, BUFFER_SIZE);
	buf.rlen = ft_strllen(sbuf[fd], '\n', buf.len);
	buf.fd = fd;
	if (!loop(&l_line, &line_len, &sbuf[fd], &buf))
		return (NULL);
	if (buf.len == -1 || l_line == NULL)
		return (free_all(l_line, &sbuf[fd]));
	*sbuf[fd] = 0;
	if ((size_t)buf.len > buf.rlen)
		save(&sbuf[fd], sbuf[fd] + buf.rlen, buf.len - buf.rlen);
	return (get_line(l_line, line_len, &sbuf[fd]));
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(int argc, char const **argv)
// {
// 	int		fd;
// 	char	*line;

// 	(void)argc;
// 	fd = open(argv[1], O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }
