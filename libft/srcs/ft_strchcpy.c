/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:26:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/23 09:39:39 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strchcpy(char *dest, const char *src, char c)
{
	int	i;
	
	i = 0;
	dest = malloc((ft_strlen(src) + 1) * sizeof(char));
	while (src && src[i] != c && src[i] != '\0')
	{
		if (src[i] == c)
			break ;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
