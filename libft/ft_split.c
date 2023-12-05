/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:56:16 by amajid            #+#    #+#             */
/*   Updated: 2023/11/05 16:20:18 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

typedef struct double_size{
	size_t	i;
	size_t	count;
}	t_double_size;

static t_double_size	calc_str_count(const char *str, char c)
{
	t_double_size	v;

	v.count = 0;
	v.i = 1;
	while (str[v.i])
	{
		if ((str[v.i] == c && str[v.i - 1] != c)
			|| (!str[v.i] && str[v.i - 1] != c))
			v.count++;
		v.i++;
	}
	if ((!str[v.i] && str[v.i - 1] != c))
		v.count++;
	v.i = 0;
	while (str[v.i] != 0 && str[v.i] != c)
	{
		v.i++;
	}
	return (v);
}

static int	safty_check(char *s)
{
	if (s == NULL)
	{
		return (0);
	}
	if (s[0] == '\0')
	{
		return (0);
	}
	return (1);
}

static void	*free_result(char **result, long index)
{
	while ((long)--index > -1)
		free(result[(long)index]);
	free(result);
	return (NULL);
}

static char	**work(char *s, char c, size_t i, size_t index)
{
	char			**result;
	t_double_size	ptr_count;
	t_double_size	i_i;

	ptr_count = calc_str_count(s, c);
	result = malloc(sizeof(char *) * (ptr_count.count + 1));
	if (!result)
		return (NULL);
	while (s[i] && index < ptr_count.count)
	{
		while (s[i] && s[i] == c)
			i++;
		i_i = calc_str_count(&s[i], c);
		result[index] = malloc(i_i.i + 1);
		if (!result[index])
			return (free_result(result, index));
		ft_strlcpy(result[index], s + i, i_i.i + 1);
		result[index][i_i.i] = '\0';
		index++;
		i += i_i.i;
	}
	result[index] = 0;
	return (result);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	index;
	char	**result;
	int		check;

	check = safty_check(s);
	if (!check)
	{
		result = malloc(sizeof(char *));
		if (!result)
			return (NULL);
		result[0] = 0;
		return (result);
	}
	i = 0;
	index = 0;
	result = work(s, c, i, index);
	return (result);
}
