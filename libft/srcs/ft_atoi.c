/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 08:11:58 by vkettune          #+#    #+#             */
/*   Updated: 2024/01/03 05:46:50 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	is_neg;
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (s[i] == '\f' || s[i] == '\t' || s[i] == ' '
		|| s[i] == '\n' || s[i] == '\r' || s[i] == '\v' )
		i++;
	is_neg = 1;
	if (s[i] == '-')
		is_neg *= -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] != '\0' && ft_isdigit(s[i]))
		res = (res * 10) + s[i++] - '0';
	return (res * is_neg);
}
