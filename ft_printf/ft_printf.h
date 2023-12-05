/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:44:21 by amajid            #+#    #+#             */
/*   Updated: 2023/11/11 20:31:37 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *str, ...);
void	c_hand(char c, int fd);
char	*ft_itoh(unsigned long long val, char prefix);
char	*ft_uitoa(unsigned int n);
char	*ft_itohi(unsigned int val, char prefix);
long	handle_conversion(va_list list, const char *s);
long	x(va_list list);
long	xx(va_list list);
long	c(va_list list);
long	per(void);
long	u(va_list list);
long	conver_help0(long i, long start, char *s, long *total);
long	conver_help1(long i, long start, char *s, long *total);

#endif