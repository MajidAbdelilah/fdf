/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:12:23 by amajid            #+#    #+#             */
/*   Updated: 2023/11/10 17:18:13 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	x(va_list list)
{
	char	*str;
	size_t	size;

	str = ft_itohi((va_arg(list, unsigned long)), 'a');
	if (!str)
		return (-1);
	ft_putstr_fd(str, 1);
	size = ft_strlen(str);
	free(str);
	return (size);
}

long	xx(va_list list)
{
	char	*str;
	size_t	size;

	str = ft_itohi((va_arg(list, unsigned long)), 'A');
	if (!str)
		return (-1);
	ft_putstr_fd(str, 1);
	size = ft_strlen(str);
	free(str);
	return (size);
}

long	c(va_list list)
{
	ft_putchar_fd((char )va_arg(list, int), 1);
	return (1);
}

long	per(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

long	u(va_list list)
{
	char	*str;
	size_t	size;

	str = ft_uitoa((va_arg(list, unsigned int)));
	if (!str)
		return (-1);
	ft_putstr_fd(str, 1);
	size = ft_strlen(str);
	free(str);
	return (size);
}
