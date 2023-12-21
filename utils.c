/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:52:42 by amajid            #+#    #+#             */
/*   Updated: 2023/12/21 18:23:49 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

float	get_scale(t_loop_data d, t_main *m,
	t_matrix4f rotation, t_matrix4f pers)
{
	t_point	p;
	t_point	xy;
	t_point	scale;

	p = d.result[0];
	p = point_matrix_multiply(pers, point_matrix_multiply(rotation, p));
	xy = (t_point){p.x, p.x, p.y, p.y};
	m->i = 0;
	while (m->i < m->size)
	{
		p = d.result[m->i];
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
	return (scale.z);
}

// t = {aspectRatio, halfWidth, halfHeight, scale};

void	get_matrix(t_loop_data *mlx, t_main m)
{
	t_point		t;
	t_matrix4f	rotation;

	t.x = (float)W / H;
	t.y = 1.0f;
	t.z = t.y / t.x;
	mlx->pers = orthogonal((t_point){-t.y,
			t.y, -t.z, t.z}, 1.0f, 100.0f);
	rotation = get_identity_matrix();
	rotation = matrix4x4_mul(matrix4x4_set_rotation(-45,
				(t_point){0.0f, 1.0f, 0.0f, 0.0f}), rotation);
	rotation = matrix4x4_mul(matrix4x4_set_rotation(-35,
				(t_point){1.0f, 0.0f, 0.0f, 0.0f}), rotation);
	mlx->model = rotation;
	t.w = get_scale(*mlx, &m, rotation, mlx->pers);
	(*mlx).scale = (t_point){t.w, t.w, t.w, t.w};
	(*mlx).rotation = rotation;
	(*mlx).transition = (t_point){my_abs_int(m.x_min) * t.w + 45,
		(my_abs_int(m.y_min) * t.w) / 2 + 45, 0.0f, 0};
	mlx->model = matrix4x4_mul(matrix4x4_set_translation(mlx->transition),
			matrix4x4_mul(rotation, matrix4x4_set_scale(
					(t_point){mlx->scale.x, mlx->scale.y,
					mlx->scale.z, 1.0f})));
}
