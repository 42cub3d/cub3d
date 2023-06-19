/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:45:08 by gkwon             #+#    #+#             */
/*   Updated: 2023/06/19 16:46:02 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
		{
			if ((unsigned char)*s1 > (unsigned char)*s2)
				return (1);
			else if ((unsigned char)*s1 < (unsigned char)*s2)
				return (-1);
		}
		s1++;
		s2++;
		n--;
		if (n == 0)
			return (0);
	}
	if ((unsigned char)*s1 > (unsigned char)*s2)
		return (1);
	else if ((unsigned char)*s1 < (unsigned char)*s2)
		return (-1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	unsigned char	*tmp;
	unsigned int	len;

	if (!count && !size)
		return (ft_strdup(""));
	len = size * count;
	ret = malloc(len);
	if (!ret)
		return (NULL);
	tmp = (unsigned char *)ret;
	while (len--)
		*tmp++ = 0;
	return (ret);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}