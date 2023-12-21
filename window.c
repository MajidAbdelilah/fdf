/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:41:50 by amajid            #+#    #+#             */
/*   Updated: 2023/12/21 18:42:24 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "/usr/local/include/mlx.h"
#include <stdlib.h>

int	mlx_close(t_loop_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	free(vars->result);
	exit(0);
	return (0);
}

int	esc_close(int keycode, t_loop_data *vars)
{
	if (keycode != 53)
		return (0);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	free(vars->result);
	exit(0);
	return (0);
}
