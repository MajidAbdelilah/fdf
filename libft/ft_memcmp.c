/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:50:56 by amajid            #+#    #+#             */
/*   Updated: 2023/11/04 13:48:43 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	if (n == 0)
		return (0);
	i = 0;
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while (i < n && s1_uc[i] == s2_uc[i])
		i++;
	if (i == n && i != 0)
		i--;
	return (s1_uc[i] - s2_uc[i]);
}
