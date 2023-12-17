#include "fdf.h"
#include <math.h>
float get_scale(t_loop_data d, t_main *m, t_matrix4f rotation, t_matrix4f pers)
{
	m->i = 0;
	t_point p = d.result[0];
	p = point_matrix_multiply(rotation, p);
	p = point_matrix_multiply(pers, p);
	int x_max = p.x;
	int x_min = p.x;
	int y_max = p.y;
	int y_min = p.y;
	m->i = 0;
	while(m->i < m->size)
	{
		t_point p = d.result[m->i];
		p = point_matrix_multiply(rotation, p);
		p = point_matrix_multiply(pers, p);
		x_max = get_max(x_max, p.x);
		y_max = get_max(y_max, p.y);
		x_min = get_min(x_min, p.x);
		y_min = get_min(y_min, p.y);
		m->i++;
	}

	float scale_x = (float)(1920 - 400) / (my_abs_int(x_max) + my_abs_int(x_min));
	float scale_y = (float)(1080 - 400) / (my_abs_int(y_max) + my_abs_int(y_min));
	float scale = (scale_x < scale_y) * scale_x + !(scale_x < scale_y) * scale_y;
	m->x_min = x_min;
	m->y_min = y_min;
	return scale;
}

void get_matrix(t_loop_data *mlx, t_main m)
{
	float aspectRatio = (float)1920/1080;
	float halfWidth = 1.0f;
	float halfHeight = halfWidth/aspectRatio;
	t_matrix4f pers = orthogonal(-halfWidth, halfWidth, -halfHeight, halfHeight, 1.0f, 100.0f);
	t_matrix4f rotation = IDENTITY_MATRIX;
	rotation = Matrix4x4_mul(matrix4x4_set_rotation(-45, (t_point){0.0f,1.0f,0.0f, 0.0f}), rotation);
	rotation = Matrix4x4_mul(matrix4x4_set_rotation(-35, (t_point){1.0f,0.0f,0.0f, 0.0f}), rotation);
	mlx->model = rotation;
	float scale = get_scale(*mlx, &m, rotation, pers);
	(*mlx).scale = (t_point){scale, scale, scale, scale};
	(*mlx).rotation = rotation;
	(*mlx).transition = (t_point){my_abs_int(m.x_min) * scale + 30, (my_abs_int(m.y_min) * scale) + 30, 0.0f, 0};
	mlx->model = Matrix4x4_mul(matrix4x4_set_translation(mlx->transition), Matrix4x4_mul(rotation, matrix4x4_set_scale((t_point){mlx->scale.x, mlx->scale.y, mlx->scale.z, 1.0f})));
	mlx->pers = pers;
}
