/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:38:53 by amajid            #+#    #+#             */
/*   Updated: 2023/12/05 19:52:40 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "ft_printf.h"
static char	*work(char *re_holder, int i)
{
	int		index;
	char	*result;

	result = malloc(i + 1);
	if (!result)
		return (NULL);
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
	return (result);
}

char	*ft_uitoa(unsigned int n)
{
	char	re_holder[32];
	long	holder;
	int		i;
	char	*result;

	if (n == 0)
	{
		result = ft_calloc(2, 1);
		if (!result)
			return (NULL);
		result[0] = '0';
		return (result);
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
	return (work(re_holder, i));
}
