/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:47:53 by amajid            #+#    #+#             */
/*   Updated: 2023/12/05 19:46:19 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdarg.h>
#include <stdlib.h>

static long	handle3(va_list list, char *s, long *total, long *i)
{
	long	ret;

	ret = handle_conversion(list, s - 1);
	if (ret == -1)
		return (-1);
	if (ret != -2)
		(*i)++;
	*total += ret * (ret > 0);
	return (0);
}

static long	helper_last(long *total, long *i, char *s)
{
	char	*str;
	long	start;

	start = *i;
	while (s[*i] != '%' && s[*i])
		(*i)++;
	str = malloc(*i - start + 1);
	if (!str)
		return (-1);
	ft_strlcpy(str, s + start, *i - start + 1);
	if (ft_putstr_fd(str, 1) == -1)
	{
		free(str);
		return (-1);
	}
	*total += *i - start;
	free(str);
	return (0);
}

static long	parse_until_per(const char *s, va_list list)
{
	long	i;
	long	start;
	long	total;

	i = 0;
	total = 0;
	while (s[i])
	{
		start = i;
		while (s[i] == '%')
			i++;
		if (!((i - start) % 2))
			if (conver_help0(i, start, (char *)s, &total) == -1)
				return (-1);
		if (((i - start) % 2))
			if (conver_help1(i, start, (char *)s, &total) == -1)
				return (-1);
		if (i && s[i - 1] == '%' && ((i - start) % 2) && s[i])
			if (handle3(list, (char *)s + i, &total, &i) == -1)
				return (-1);
		if (helper_last(&total, &i, (char *)s) == -1)
			return (-1);
	}
	return (total);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	long	ret;

	va_start(list, str);
	ret = parse_until_per(str, list);
	va_end(list);
	return (ret);
}
