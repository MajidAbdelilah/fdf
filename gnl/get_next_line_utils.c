/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:11:53 by amajid            #+#    #+#             */
/*   Updated: 2023/11/18 15:30:44 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long	ft_strlen(const char *s)
{
	long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, long n)
{
	long			i;
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

long	ft_strlcpy(char *dst, const char *src, long dstsize)
{
	long	i;

	if (!dstsize)
	{
		if (src)
			return (ft_strlen(src));
		else
			return (0);
	}
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	i++;
	return (i);
}

char	gnl_init(t_vars *v, char run_first)
{
	(*v).ret_buf = 0;
	if ((*v).is_1_call && !(*v).buffer && run_first)
		(*v) = (t_vars){.buffer = 0, .buffer_swap = 0, .is_1_call = 0,
			.i = 0, .j = 0, .start = 0, .read_ret = 0, .size = 1000000};
	if (!(*v).is_1_call && run_first)
	{
		(*v).size = 1000000;
		(*v).buffer = malloc((*v).size);
		if (!(*v).buffer)
			return (0);
	}
	if ((*v).read_ret == -1 && !run_first)
	{
		free((*v).buffer);
		(*v).buffer = NULL;
		(*v).is_1_call = 1;
		return (0);
	}
	return (1);
}
