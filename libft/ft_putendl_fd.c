/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:49 by amajid            #+#    #+#             */
/*   Updated: 2023/12/21 18:49:28 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putendl_fd(char *s, int fd)
{
	size_t	size;
	int		ret;

	ret = 0;
	if (!s)
		return (0);
	size = ft_strlen(s);
	ret += write(fd, s, size);
	write(fd, "\n", 1);
	if (ret == -1)
		return (ret);
	return (ret + 1);
}
