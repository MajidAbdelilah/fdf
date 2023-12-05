/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:09:51 by amajid            #+#    #+#             */
/*   Updated: 2023/11/05 18:28:55 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	b_count(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	is_found;

	i = 0;
	while (s1[i])
	{
		j = 0;
		is_found = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				is_found = 1;
				break ;
			}
			j++;
		}
		if (!is_found)
			break ;
		i++;
	}
	return (i);
}

static size_t	a_count(char const *s1, char const *set)
{
	long	i;
	size_t	j;
	char	is_found;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	i = s1_len - 1;
	while (i > -1)
	{
		j = 0;
		is_found = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				is_found = 1;
				break ;
			}
			j++;
		}
		if (!is_found)
			break ;
		i--;
	}
	return (s1_len - i - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	s1_len;
	size_t	b_len;
	size_t	a_len;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	b_len = b_count(s1, set);
	a_len = 0;
	if (b_len != s1_len)
		a_len = a_count(s1, set);
	result = malloc((s1_len - a_len) - b_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + b_len, (s1_len - b_len) - a_len + 1);
	result[(s1_len - b_len) - a_len] = 0;
	return (result);
}
