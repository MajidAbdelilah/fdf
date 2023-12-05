/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:41:03 by amajid            #+#    #+#             */
/*   Updated: 2023/12/05 19:51:55 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

static long	str(va_list list)
{
	char	*str;
	size_t	size;

	str = (char *)va_arg(list, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	size = ft_strlen(str);
	if (!size)
		return (0);
	return (size);
}

static long	d(va_list list)
{
	char	*str;
	size_t	size;

	str = ft_itoa(va_arg(list, int));
	if (!str)
		return (-1);
	ft_putstr_fd(str, 1);
	size = ft_strlen(str);
	free(str);
	return (size);
}

static long	i(va_list list)
{
	char	*str;
	size_t	size;

	str = ft_itoa(va_arg(list, int));
	if (!str)
		return (-1);
	ft_putstr_fd(str, 1);
	size = ft_strlen(str);
	free(str);
	return (size);
}

static long	p(va_list list)
{
	char	*str;
	size_t	size;

	str = ft_itoh((unsigned long)(va_arg(list, char *)), 'a');
	if (!str)
		return (-1);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(str, 1);
	size = ft_strlen(str) + 2;
	free(str);
	return (size);
}

long	handle_conversion(va_list list, const char *s)
{
	if (s[1] == 'c')
		return (c(list));
	else if (s[1] == '%')
		return (per());
	else if (s[1] == 's')
		return (str(list));
	else if (s[1] == 'd')
		return (d(list));
	else if (s[1] == 'i')
		return (i(list));
	else if (s[1] == 'p')
		return (p(list));
	else if (s[1] == 'u')
		return (u(list));
	else if (s[1] == 'x')
		return (x(list));
	else if (s[1] == 'X')
		return (xx(list));
	return (-2);
}
