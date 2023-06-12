/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:20:55 by subcho            #+#    #+#             */
/*   Updated: 2023/06/12 14:42:25 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	start;
	size_t	finish;
	size_t	len;

	if (!s1[0] || !set[0])
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	finish = ft_strlen(s1) - 1;
	while (s1[finish] && ft_strchr(set, s1[finish]))
		finish--;
	finish += 1;
	if (finish == 0)
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * (finish - start) + 1);
	if (!p)
		return (0);
	len = finish - start;
	while (start < finish)
		*(p++) = s1[start++];
	*p = 0;
	return (p - len);
}
