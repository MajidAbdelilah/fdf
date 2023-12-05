/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:21:26 by amajid            #+#    #+#             */
/*   Updated: 2023/11/10 17:55:18 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	conver_help0(long i, long start, char *s, long *total)
{
	char	*str;

	str = malloc(i - start + 1);
	if (!str)
		return (-1);
	ft_strlcpy(str, s + start, i - start + 1);
	str[(i - start) / 2] = 0;
	if (ft_putstr_fd(str, 1) == -1)
	{
		free(str);
		return (-1);
	}
	*total += (i - start) / 2;
	free(str);
	return (0);
}

long	conver_help1(long i, long start, char *s, long *total)
{
	char	*str;

	str = malloc(i - start);
	if (!str)
		return (-1);
	ft_strlcpy(str, s + start, i - start);
	str[(i - start - 1) / 2] = 0;
	if (ft_putstr_fd(str, 1) == -1)
	{
		free(str);
		return (-1);
	}
	*total += (i - start - 1) / 2;
	free(str);
	return (0);
}
