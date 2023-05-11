/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:35:07 by subcho            #+#    #+#             */
/*   Updated: 2023/01/30 19:30:48 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_total_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

int	get_word_count(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i] && str[i] == c)
			break ;
	}
	return (i);
}

char	*get_word(char *str, int word_count)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * word_count + 1);
	if (!word)
		return (0);
	while (i < word_count)
	{
		word[i] = *str;
		i++;
		str++;
	}
	word[i] = '\0';
	return (word);
}

char	**free_null(char **result, int total_count)
{
	int	i;

	i = 0;
	while (i < total_count)
	{
		if (!result[i])
		{
			i = 0;
			while (i < total_count)
				free(result[i++]);
			free(result);
			return (0);
		}
		i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		total_count;
	int		word_count;
	int		i;

	total_count = get_total_count((char *)s, c);
	result = (char **)malloc(sizeof(char *) * (total_count + 1));
	if (!result)
		return (0);
	i = 0;
	while (*s && i < total_count)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			word_count = get_word_count((char *)s, c);
			result[i++] = get_word((char *)s, word_count);
			s += word_count;
		}
	}
	result[i] = 0;
	result = free_null(result, total_count);
	return (result);
}
