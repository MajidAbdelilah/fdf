#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include "mlx/mlx.h"



int	loop(void *data)
{
	//t_loop_data d = *(t_loop_data*)data;
	(void)data;
	// exit(0);
	return 0;
}
int	close(t_loop_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	
	free(vars->result);
	free(vars->mlx);
	//free(vars->img.addr);
	exit(0);
	//vars->mlx = 0;
	//vars->mlx_win = 0;
	
	return (0);
}

int	esc_close(int keycode, t_loop_data *vars)
{
	if(keycode != 53)
		return 0;
	
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	
	free(vars->result);
	free(vars->mlx);
	//free(vars->img.addr);
	exit(0);
	//vars->mlx = 0;
	//vars->mlx_win = 0;
	return (0);
}

void draw(t_loop_data d, t_main m, t_matrix4f pers)
{
while(m.i < (m.size))
	{
		t_point p = d.result[m.i];
		p = point_matrix_multiply(d.model, p);
		p = point_matrix_multiply(pers, p);		
		t_point p2;
		if((m.i % m.i_i) == 0)
		{
			m.i_size = m.last_line_index;
			m.last_line_index = m.i;
			m.j = 0;
			m.up = 1;
		}else {
			p2 = d.result[m.i-1];
			p2 = point_matrix_multiply(d.model, p2);
			p2 = point_matrix_multiply(pers, p2);
			if(p2.x > 1920 || p2.x < 0 || p2.y > 1080 || p2.y < 0 || p.x > 1920 || p.x < 0 || p.y > 1080 || p.y < 0)
				{
					m.i++;
					continue;
				}
			if(d.result[m.i].y < 0.0f || d.result[m.i-1].y < 0.0f)
				DDA(p.x, p.y, p2.x, p2.y, &d.img, 0x00990000);
			else
			 	DDA(p.x, p.y, p2.x, p2.y, &d.img, 0x00000099);
		}
		if(m.up)
		{
			p2 = d.result[m.i - m.i_i];
			p2 = point_matrix_multiply(d.model, p2);
			p2 = point_matrix_multiply(pers, p2);
			if(p2.x > 1920 || p2.x < 0 || p2.y > 1080 || p2.y < 0 || p.x > 1920 || p.x < 0 || p.y > 1080 || p.y < 0)
				{
					m.i++;
					continue;
				}
			if(d.result[m.i].y < 0.0f || d.result[m.i - m.i_i].y < 0.0f)
				DDA(p.x, p.y, p2.x, p2.y, &d.img, 0x00990000);
			else
				DDA(p.x, p.y, p2.x, p2.y, &d.img, 0x00000099);
			m.j++;
		}
		m.i++;
	}
}

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

	float scale_x = (float)(1920 - 400) / (abs(x_max) + abs(x_min));
	float scale_y = (float)(1080 - 400) / (abs(y_max) + abs(y_min));
	float scale = (scale_x < scale_y) * scale_x + !(scale_x < scale_y) * scale_y;
	m->x_min = x_min;
	m->y_min = y_min;
	return scale;
}

int main(int argnum, char **args)
{
	(void)(argnum);
	int map = open(args[1], O_RDONLY);
	t_main m = {0};
	t_point *result = get_split_fdf(map, &m.size, &m.i_i, &m.j_j);
	
	t_loop_data mlx = {0};
	mlx.result = result;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 1920, 1080, "FDF");
	mlx.img.img = mlx_new_image(mlx.mlx, 1920, 1080);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel, &mlx.img.line_length,
								&mlx.img.endian);
	mlx_hook(mlx.mlx_win, 17, 0L, close, &mlx);
	mlx_hook(mlx.mlx_win, 2, 1L<<0, esc_close, &mlx);

	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// i = 1;
	float aspectRatio = (float)1920/1080;

 // generate perspective matrix  
    
       float halfWidth = 1.0f;
       float halfHeight = halfWidth/aspectRatio;
	t_matrix4f pers = orthogonal(-halfWidth, halfWidth, -halfHeight, halfHeight, 1.0f, 100.0f);

	t_matrix4f model = IDENTITY_MATRIX;
	t_matrix4f rotation = IDENTITY_MATRIX;

	rotation = Matrix4x4_mul(matrix4x4_set_rotation(-45, (t_point){0.0f,1.0f,0.0f, 0.0f}), rotation);
	rotation = Matrix4x4_mul(matrix4x4_set_rotation(-35, (t_point){1.0f,0.0f,0.0f, 0.0f}), rotation);
	mlx.model = rotation;
//	t_matrix4f iso = get_isometric_matrix();
	float scale = get_scale(mlx, &m, rotation, pers);



	model = Matrix4x4_mul(matrix4x4_set_translation((t_point){ abs(m.x_min) * scale + 30, (abs(m.y_min) * scale) + 30, 0.0f, 0}), Matrix4x4_mul(rotation, matrix4x4_set_scale((t_point){scale, scale, scale, 1.0f})));
	m.i = 1;
	mlx.model = model;
	draw(mlx, m, pers);	
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
	mlx_loop_hook(mlx.mlx, loop, 0);
	mlx_loop(mlx.mlx);
	return 0;
}