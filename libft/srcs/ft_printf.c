/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:54:01 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/03 08:11:45 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_error(int value, int check)
{
	if (value == -1 || check == -1)
		return (-1);
	return (value + check);
}

int	ft_conversion(va_list args, const char format)
{
	int	c;

	c = 0;
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_printptr(va_arg(args, unsigned long long), &c));
	else if (format == 'd' || format == 'i')
		return (ft_printnbr(va_arg(args, int), &c));
	else if (format == 'u')
		return (ft_printunsigned(va_arg(args, unsigned int), &c));
	else if (format == 'x' || format == 'X')
		return (ft_printhex(va_arg(args, unsigned int), format, &c));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		printed;
	int		check;
	va_list	args;

	printed = 0;
	if (!str || *str == '\0')
		return (0);
	va_start (args, str);
	while (*str)
	{
		if (*str == '%')
			printed += ft_conversion(args, *(++str));
		else
			printed += ft_putchar(*str);
		check = ft_check_error(printed, check);
		if (check == -1)
			return (-1);
		str++;
	}
	va_end(args);
	return (printed);
}
