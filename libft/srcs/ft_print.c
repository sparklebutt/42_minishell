/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:13:27 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/03 08:11:41 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
	{
		if (ft_printstr("(null)") == -1)
			return (-1);
		return (6);
	}
	while (str[i])
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_printnbr(int nbr, int *c)
{
	int	a;

	a = 0;
	if (nbr == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		nbr = -nbr;
		(*c)++;
	}
	if (nbr > 9)
		if (ft_printnbr(nbr / 10, c) == -1)
			return (-1);
	(*c)++;
	a = nbr % 10 + '0';
	if (write(1, &a, 1) == -1)
		return (-1);
	return (*c);
}

int	ft_printunsigned(unsigned int nbr, int *c)
{
	int	a;

	a = 0;
	if (nbr > 9)
		if (ft_printnbr(nbr / 10, c) == -1)
			return (-1);
	(*c)++;
	a = nbr % 10 + '0';
	if (write(1, &a, 1) == -1)
		return (-1);
	return (*c);
}

int	ft_printptr(unsigned long long ptr, int *c)
{
	int	a;

	a = 0;
	if (write(1, "0x", 2) == -1)
		return (-1);
	a = ft_printhex(ptr, 'x', c);
	if (a == -1)
		return (-1);
	return (a + 2);
}

int	ft_printhex(unsigned long long nbr, char format, int *c)
{
	int	a;

	a = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr >= 16)
	{
		(*c)++;
		if (ft_printhex(nbr / 16, format, c) == -1)
			return (-1);
		(*c)++;
		a = ft_printhex(nbr % 16, format, c);
	}
	else
	{
		if (nbr < 10)
			a = ft_putchar(nbr + '0');
		else
			a = ft_putchar(nbr - 10 + (format - 23));
	}
	if (a == -1)
		return (-1);
	return (ft_len(nbr));
}
