/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:36:32 by amajid            #+#    #+#             */
/*   Updated: 2023/12/20 20:07:45 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	my_abs(float n)
{
	char	is_bigger;

	is_bigger = (n > 0.0f);
	return (is_bigger * n + !is_bigger * (n * (-1.0f)));
}

int	my_abs_int(int n)
{
	char	is_bigger;

	is_bigger = (n > 0);
	return (is_bigger * n + !is_bigger * (n * (-1)));
}

int	get_max(int x, int y)
{
	char	is_x;

	is_x = (x > y);
	return (x * is_x + y * !is_x);
}

int	get_min(int x, int y)
{
	char	is_x;

	is_x = (x < y);
	return (x * is_x + y * !is_x);
}

t_matrix4f	matrix4x4_set_translation(t_point vecPos)
{
	t_matrix4f	result;

	result = get_identity_matrix();
	result.m[3][0] = vecPos.x;
	result.m[3][1] = vecPos.y;
	result.m[3][2] = vecPos.z;
	return (result);
}
