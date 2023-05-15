/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:45:08 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/15 17:27:11 by gkwon            ###   ########.fr       */
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