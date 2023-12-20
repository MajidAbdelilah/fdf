/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:38:40 by amajid            #+#    #+#             */
/*   Updated: 2023/12/20 20:12:04 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <sys/fcntl.h>
#include "/usr/local/include/mlx.h"
#include <stdio.h>
#include <unistd.h>

int	loop(t_all *data)
{
	animate(data->mlx);
	clear_img(data->mlx);
	draw(*data->mlx, *data->m);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win,
		data->mlx->img.img, 0, 0);
	return (0);
}

void	init(t_loop_data *mlx, t_main *m, int map)
{
	t_point	*result;

	result = get_split_fdf(map, &m->size, &m->i_i, &m->j_j);
	mlx->result = result;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, W, H, "FDF");
	mlx->img.img = mlx_new_image(mlx->mlx, W, H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	mlx_hook(mlx->mlx_win, 17, 0L, mlx_close, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L << 0, handle_keys, mlx);
	close(map);
}

#include <stdlib.h>
void check()
{
	system("leaks bonus");
}

int	main(int argnum, char **args)
{
	int			map;
	t_main		m;
	t_loop_data	mlx;

	atexit(check);
	(void)(argnum);
	map = open(args[1], O_RDONLY);
	m = (t_main){0};
	mlx = (t_loop_data){0};
	init(&mlx, &m, map);
	get_matrix(&mlx, m);
	m.i = 1;
	draw(mlx, m);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
	mlx_loop_hook(mlx.mlx, loop, (t_all[]){{&mlx, &m}});
	mlx_loop(mlx.mlx);
	return (0);
}
