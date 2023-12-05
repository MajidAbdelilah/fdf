/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:29:54 by amajid            #+#    #+#             */
/*   Updated: 2023/11/06 15:46:45 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	work(char *re_holder, int i, char *result)
{
	int		index;

	if (!result)
		return ;
	result[0] = re_holder[0];
	index = (re_holder[0] == '-');
	i--;
	while (re_holder[index])
	{
		result[index] = re_holder[i];
		index++;
		i--;
	}
	result[index] = 0;
}

static void	ft_itoa_ptr(int n, char *result)
{
	char	re_holder[32];
	long	holder;
	int		i;

	if (n == 0)
	{
		if (!result)
			return ;
		result[0] = '0';
		result[1] = 0;
		return ;
	}
	i = 0;
	holder = n;
	holder *= (n < 0) * -1 + !(n < 0);
	while (holder)
	{
		re_holder[i++] = (holder % 10) + '0';
		holder /= 10;
	}
	re_holder[i] = (n < 0) * '-';
	i += (n < 0);
	re_holder[i] = 0;
	(work(re_holder, i, result));
}

void	ft_putnbr_fd(int n, int fd)
{
	char	result[32];

	ft_itoa_ptr(n, result);
	write(fd, result, ft_strlen(result));
	return ;
}
