/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:16:25 by amajid            #+#    #+#             */
/*   Updated: 2023/11/04 18:58:29 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	h_len;
	size_t	n_len;

	if (!len)
	{
		n_len = ft_strlen(needle);
		if (!n_len)
			return ((char *)haystack);
		else
			return (NULL);
	}
	n_len = ft_strlen(needle);
	h_len = ft_strlen(haystack);
	if (!n_len)
		return ((char *)haystack);
	i = 0;
	while ((i + n_len) <= len && haystack[i])
	{
		if (!ft_strncmp(haystack + i, needle, n_len))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
