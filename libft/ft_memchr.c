/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:22:08 by amajid            #+#    #+#             */
/*   Updated: 2023/11/04 13:28:52 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_uc;
	unsigned char	c_uc;

	i = 0;
	s_uc = (unsigned char *)s;
	c_uc = (unsigned char)c;
	while (i < n)
	{
		if (s_uc[i] == c_uc)
			return (s_uc + i);
		i++;
	}
	return (NULL);
}
