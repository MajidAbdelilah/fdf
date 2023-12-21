/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:10:44 by amajid            #+#    #+#             */
/*   Updated: 2023/12/21 17:57:12 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	dda(t_point p, t_data *data, int color)
{
	float		steps;
	t_point		dda;
	long long	i;
	char		is_x;

	dda.x = p.z - p.x;
	dda.y = p.w - p.y;
	is_x = my_abs(dda.x) > my_abs(dda.y);
	steps = is_x * my_abs(dda.x) + my_abs(dda.y) * !is_x;
	dda.z = dda.x / (float)steps;
	dda.w = dda.y / (float)steps;
	i = -2;
	while (++i <= steps)
	{
		if (p.x > (W - 10) || p.x < 10 || p.y > (H - 10) || p.y < 10)
		{
			if(p.z > (W - 10) || p.z < 10 || p.w > (H - 10) || p.w < 10)
				return ;
			p.x += dda.z;
			p.y += dda.w;
			continue ;
		}
		my_mlx_pixel_put(data, round(p.x), round(p.y), color);
		p.x += dda.z;
		p.y += dda.w;
	}
}

void	clear_img(t_loop_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			my_mlx_pixel_put(&mlx->img, j, i, 0x00000000);
			j++;
		}
		i++;
	}
}

void	draw_line(t_loop_data d, t_main m, t_point p, long long index)
{
	t_point	p2;

	p2 = d.result[m.i - index];
	p2 = point_matrix_multiply(d.model, p2);
	p2 = point_matrix_multiply(d.pers, p2);
	if (d.result[m.i].y < 0.0f || d.result[m.i - index].y < 0.0f)
		dda((t_point){p.x, p.y, p2.x, p2.y}, &d.img, 0x00990000);
	else
		dda((t_point){p.x, p.y, p2.x, p2.y}, &d.img, 0x00000099);
}

void	draw(t_loop_data d, t_main m)
{
	t_point	p;

	m.i = 1;
	d.model = matrix4x4_mul(matrix4x4_set_translation(d.transition),
			matrix4x4_mul(d.rotation,
				matrix4x4_set_scale(
					(t_point){d.scale.x, d.scale.y, d.scale.z, 1.0f})));
	while (m.i < (m.size))
	{
		p = d.result[m.i];
		p = point_matrix_multiply(d.model, p);
		p = point_matrix_multiply(d.pers, p);
		if ((m.i % m.i_i) == 0)
		{
			m.i_size = m.last_line_index;
			m.last_line_index = m.i;
			m.up = 1;
		}
		else
			draw_line(d, m, p, 1);
		if (m.up)
			draw_line(d, m, p, m.i_i);
		m.i++;
	}
}
