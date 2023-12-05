/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:54:55 by amajid            #+#    #+#             */
/*   Updated: 2023/11/18 15:33:54 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef struct vars{
	char	*buffer;
	char	*buffer_swap;
	char	*ret_buf;
	char	is_1_call;
	int		i;
	int		j;
	int		start;
	int		read_ret;
	long	size;
}	t_vars;

char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, long n);
long	ft_strlen(const char *s);
long	ft_strlcpy(char *dst, const char *src, long dstsize);
char	gnl_init(t_vars *v, char is_first);

#endif