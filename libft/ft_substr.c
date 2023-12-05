/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:58:09 by amajid            #+#    #+#             */
/*   Updated: 2023/11/07 15:19:21 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*return_empty_str(void)
{
	char	*result;

	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = 0;
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*result;

	i = 0;
	if (len <= 0)
		return (return_empty_str());
	if (!s)
		return (NULL);
	if (start < 0)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= (start))
		return (return_empty_str());
	result = malloc((len < (s_len - start)) * (len + 1)
			+ (s_len - start + 1) * !(len < (s_len - start)));
	if (!result)
		return (NULL);
	while (s[start + i] && i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}
