/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:26:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/25 15:39:09 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strchcpy(char *dest, char *src, char c)
{
	int	i;
	
	i = 0;
	ft_printf("src: %s\n", src);
	ft_printf("c: %c\n", c);
	ft_printf("src[i]: %c\n", src[i]);
	i = ft_strlen(src);
	ft_printf("strlen of src: %d\n", i);
	dest = malloc((ft_strlen(src) + 1) * sizeof(char));
	while (src && src[i] != c && src[i] != '\0')
	{
		if (src[i] == c)
			break ;
		dest[i] = src[i];
		// ft_printf("dest[i]: %c\n", dest[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
