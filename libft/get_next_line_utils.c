/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:09:38 by subcho            #+#    #+#             */
/*   Updated: 2023/02/08 23:51:40 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	size_t			i;
	size_t			j;

	if (!s1 || !s1[0])
		return (ft_strdup(s2));
	if (!s2 || !s2[0])
		return (ft_strdup(s1));
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!result)
		return (0);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = 0;
	free((void *)s1);
	return (result);
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*p;
	size_t	i;

	s1 = (char *)s1;
	size = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * size + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = 0;
	return (p);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	char	*org_p;
	size_t	i;

	s1 = (char *)s1;
	i = 0;
	if (!n)
		return (0);
	p = (char *)malloc(sizeof(char) * n + 1);
	if (!p)
	{
		free((void *)s1);
		return (0);
	}
	org_p = p;
	while (*(s1 + i) && i < n)
	{
		*(p + i) = *(s1 + i);
		i++;
	}
	*(p + i) = 0;
	free((void *)s1);
	return (org_p);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

size_t	ft_strlenlf(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] && s[count] != '\n')
		count++;
	if (s[count] == '\n')
		count++;
	return (count);
}
