/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:34:32 by amajid            #+#    #+#             */
/*   Updated: 2023/11/03 19:10:55 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	work(long i, char *char_dst, char *char_src, size_t len)
{
	if (char_dst > char_src)
	{
		i = len - 1;
		while (i >= 0)
		{
			char_dst[i] = char_src[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while ((size_t)i < len)
		{
			char_dst[i] = char_src[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long	i;
	char	*char_dst;
	char	*char_src;

	if ((dst == NULL && src == NULL) || len == 0)
		return (dst);
	char_dst = (char *)dst;
	char_src = (char *)src;
	i = 0;
	work(i, char_dst, char_src, len);
	return (dst);
}
