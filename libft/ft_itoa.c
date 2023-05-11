/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subcho <subcho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 03:17:59 by subcho            #+#    #+#             */
/*   Updated: 2023/02/08 21:45:43 by subcho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*get_result(int n, char *result, int len, int flag)
{
	char	*result_cpy;

	result_cpy = result;
	if (flag)
	{
		result_cpy[0] = '-';
		while (--len > 0)
		{
			result_cpy[len] = n % 10 + '0';
			n /= 10;
		}
		return (result_cpy);
	}
	while (--len >= 0)
	{
		result_cpy[len] = n % 10 + '0';
		n /= 10;
	}
	return (result_cpy);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	int		flag;

	flag = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		flag = 1;
		n *= -1;
	}
	len = get_len(n) + flag;
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	result[len] = 0;
	result = get_result(n, result, len, flag);
	return (result);
}
