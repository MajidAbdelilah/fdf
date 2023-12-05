/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:08:16 by amajid            #+#    #+#             */
/*   Updated: 2023/11/04 17:59:57 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	if (!dstsize)
		return (ft_strlen(src));
	size = ft_strlen(dst);
	if (size > (dstsize - 1))
	{
		return (ft_strlen(src) + dstsize);
	}
	i = size;
	while (src[i - size] && i < (dstsize - 1))
	{
		dst[i] = src[i - size];
		i++;
	}
	dst[i] = 0;
	return (size + ft_strlen(src));
}
