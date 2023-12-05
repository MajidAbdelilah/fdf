/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:50:55 by amajid            #+#    #+#             */
/*   Updated: 2023/11/03 18:16:47 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_h;
	unsigned char	*src_h;

	if (!dest && !src)
		return (dest);
	i = 0;
	dest_h = (unsigned char *)dest;
	src_h = (unsigned char *)src;
	while (i < n)
	{
		dest_h[i] = src_h[i];
		i++;
	}
	return (dest);
}
