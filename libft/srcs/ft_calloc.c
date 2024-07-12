/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:28:19 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/04 14:53:26 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	temp;

	temp = size * count;
	if (count == 0 || size == 0)
	{
		dest = malloc(0);
		return (dest);
	}
	if (temp % count != 0 || temp % size != 0)
		return (NULL);
	dest = malloc(temp);
	if (!dest)
		return (NULL);
	ft_bzero(dest, temp);
	return (dest);
}

/*void	*ft_calloc(size_t count, size_t size)
{
	void	*storage_ptr;

	storage_ptr = malloc(count * size);
	if (storage_ptr == NULL)
		return (NULL);
	ft_bzero(storage_ptr, count * size);
	return (storage_ptr);
}*/
