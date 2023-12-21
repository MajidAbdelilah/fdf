/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:29:56 by amajid            #+#    #+#             */
/*   Updated: 2023/12/21 18:30:46 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include "/usr/local/include/mlx.h"
#include <stdlib.h>

void	w_rotate(int keycode, t_loop_data *vars)
{
	if (keycode == 31)
		rotate(vars, (t_point){1, 0, 0, 0}, 0);
	if (keycode == 37)
		rotate(vars, (t_point){1, 0, 0, 0}, 1);
	if (keycode == 34)
		rotate(vars, (t_point){0, 1, 0, 0}, 0);
	if (keycode == 40)
		rotate(vars, (t_point){0, 1, 0, 0}, 1);
	if (keycode == 32)
		rotate(vars, (t_point){0, 0, 1, 0}, 0);
	if (keycode == 38)
		rotate(vars, (t_point){0, 0, 1, 0}, 1);
}

void	w_translate_scale(int keycode, t_loop_data *vars)
{
	if (keycode == 12)
		translate(vars, (t_point){1, 0, 0, 0}, 0);
	if (keycode == 0)
		translate(vars, (t_point){1, 0, 0, 0}, 1);
	if (keycode == 13)
		translate(vars, (t_point){0, 1, 0, 0}, 0);
	if (keycode == 1)
		translate(vars, (t_point){0, 1, 0, 0}, 1);
	if (keycode == 78)
		scale(vars, (t_point){1, 1, 1, 0}, 0);
	if (keycode == 69)
		scale(vars, (t_point){1, 1, 1, 0}, 1);
	if (keycode == 7)
		vars->animate = !vars->animate;
	if (keycode == 6)
		multiview_orthographic_projection(vars);
}

int	handle_keys(int keycode, t_loop_data *vars)
{
	w_rotate(keycode, vars);
	w_translate_scale(keycode, vars);
	if (keycode != 53)
		return (0);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	free(vars->result);
	exit(0);
	return (0);
}
