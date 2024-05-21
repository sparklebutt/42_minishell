/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:51:29 by vkettune          #+#    #+#             */
/*   Updated: 2024/01/03 05:47:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(int n)
{
	int	l;

	l = 0;
	if (n <= 0)
		l++;
	while (n)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*res;

	l = len(n);
	res = (char *)malloc(sizeof(char) * (l + 1));
	if (!res)
		return (0);
	res[l--] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		if (n == -2147483648)
			res[l--] = '8';
		if (n == -2147483648)
			n = n / 10;
		n = n * -1;
		res[0] = '-';
	}
	while (n > 0)
	{
		res[l--] = n % 10 + '0';
		n = n / 10;
	}
	return (res);
}
