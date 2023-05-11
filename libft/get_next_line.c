/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:08:30 by subcho            #+#    #+#             */
/*   Updated: 2023/01/30 17:46:50 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char) c;
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (c == 0)
		return ((char *) s);
	return (0);
}

size_t	get_end(char *txt)
{
	if (!txt)
		return (0);
	if (!txt[0])
	{
		free(txt);
		txt = 0;
		return (0);
	}
	return (1);
}

char	*get_txt(char *txt, int fd, ssize_t buffer_size)
{
	ssize_t		read_size;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
	read_size = read(fd, buffer, buffer_size);
	if (read_size < 0)
	{
		if (txt)
		{
			free(txt);
			txt = 0;
		}
		free(buffer);
		return (0);
	}
	buffer[read_size] = 0;
	if (!txt && read_size > 0)
		txt = ft_strdup(buffer);
	else if (txt && read_size > 0)
		txt = ft_strjoin(txt, buffer);
	txt = find_lf_or_eof(txt, buffer, fd, buffer_size);
	free(buffer);
	return (txt);
}

char	*find_lf_or_eof(char *txt, char *buffer, int fd, ssize_t buffer_size)
{
	ssize_t		read_size;

	while (txt)
	{
		if (ft_strchr(txt, '\n'))
			break ;
		read_size = read(fd, buffer, buffer_size);
		if (read_size <= 0)
			break ;
		buffer[read_size] = 0;
		txt = ft_strjoin(txt, buffer);
	}
	return (txt);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	char		*temp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	txt = get_txt(txt, fd, BUFFER_SIZE);
	if (!get_end(txt))
		return (0);
	temp = ft_strdup(txt);
	free(txt);
	txt = ft_strdup(temp + ft_strlenlf(temp));
	temp = ft_strndup(temp, ft_strlenlf(temp));
	if (!txt[0])
	{
		free(txt);
		txt = 0;
	}
	return (temp);
}
