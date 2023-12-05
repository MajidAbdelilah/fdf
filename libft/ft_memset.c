/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:53:47 by amajid            #+#    #+#             */
/*   Updated: 2023/11/03 19:11:15 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*result;
	size_t			i;

	i = 0;
	result = (unsigned char *)s;
	while (i != n)
	{
		result[i] = (unsigned char)c;
		i++;
	}
	return (result);
}
