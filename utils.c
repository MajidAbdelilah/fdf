/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:52:42 by amajid            #+#    #+#             */
/*   Updated: 2023/12/21 17:51:52 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

float get_scale(t_loop_data d, t_main *m, t_matrix4f rotation, t_matrix4f pers)
{
	t_point	p;
	t_point	xy;
	t_point scale;
	
	p = d.result[0];
	p = point_matrix_multiply(pers, point_matrix_multiply(rotation, p));
	xy = (t_point){p.x, p.x, p.y, p.y};
	m->i = 0;
	while(m->i < m->size)
	{
		t_point p = d.result[m->i];
		p = point_matrix_multiply(pers, point_matrix_multiply(rotation, p));
		xy = (t_point){.x = get_max(xy.x, p.x), .z = get_max(xy.z, p.y),
				.y = get_min(xy.y, p.x), .w = get_min(xy.w, p.y)};
		m->i++;
	}
	scale.x = (float)(W - 50) / (my_abs_int(xy.x) + my_abs_int(xy.y));
	scale.y = (float)(H - 50) / (my_abs_int(xy.z) + my_abs_int(xy.w));
	scale.z = (scale.x < scale.y) * scale.x + !(scale.x < scale.y) * scale.y;
	m->x_min = xy.y;
	m->y_min = xy.w;
	return scale.z;
}

void get_matrix(t_loop_data *mlx, t_main m)
{
	float aspectRatio = (float)W/H;
	float halfWidth = 1.0f;
	float halfHeight = halfWidth/aspectRatio;
	t_matrix4f pers = orthogonal((t_point){-halfWidth, halfWidth, -halfHeight, halfHeight}, 1.0f, 100.0f);
	t_matrix4f rotation = get_identity_matrix();
	rotation = matrix4x4_mul(matrix4x4_set_rotation(-45, (t_point){0.0f,1.0f,0.0f, 0.0f}), rotation);
	rotation = matrix4x4_mul(matrix4x4_set_rotation(-35, (t_point){1.0f,0.0f,0.0f, 0.0f}), rotation);
	mlx->model = rotation;
	float scale = get_scale(*mlx, &m, rotation, pers);
	(*mlx).scale = (t_point){scale, scale, scale, scale};
	(*mlx).rotation = rotation;
	(*mlx).transition = (t_point){my_abs_int(m.x_min) * scale + 45, (my_abs_int(m.y_min) * scale) / 2 + 45, 0.0f, 0};
	mlx->model = matrix4x4_mul(matrix4x4_set_translation(mlx->transition), matrix4x4_mul(rotation, matrix4x4_set_scale((t_point){mlx->scale.x, mlx->scale.y, mlx->scale.z, 1.0f})));
	mlx->pers = pers;
}
