#include "fdf.h"
#include <sys/fcntl.h>
#include "mlx.h"
#include <stdio.h>
int rotate(t_loop_data *data, char x, char y, char z, char direction)
{
	if(x && direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(5, (t_point){1.0f, 0.0f,  0.0f,  0.0f}), data->rotation);
	if(x && !direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(-5, (t_point){1.0f, 0.0f,  0.0f,  0.0f}), data->rotation);

	if(y && direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(5, (t_point){0.0f, 1.0f,  0.0f,  0.0f}), data->rotation);
	if(y && !direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(-5, (t_point){0.0f, 1.0f,  0.0f,  0.0f}), data->rotation);

	if(z && direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(5, (t_point){0.0f, 0.0f,  1.0f,  0.0f}), data->rotation);
	if(z && !direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(-5, (t_point){0.0f, 0.0f,  1.0f,  0.0f}), data->rotation);
	return 0;
}

int translate(t_loop_data *data, char x, char y, char z, char direction)
{
	if(x && direction)
		data->transition.x += 10.0f;
	if(x && !direction)
		data->transition.x -= 10.0f;
	if(y && direction)
		data->transition.y += 10.0f;
	if(y && !direction)
		data->transition.y -= 10.0f;

	if(z && direction)
		data->transition.z += 10.0f;
	if(z && !direction)
		data->transition.z -= 10.0f;
	return 0;
}

int scale(t_loop_data *data, char x, char y, char z, char direction)
{
	if(x && direction)
		data->scale.x += data->scale.x / 5;
	if(x && !direction)
		data->scale.x -= data->scale.x / 5;
	
	if(y && direction)
		data->scale.y += data->scale.y / 5;
	if(y && !direction)
		data->scale.y -= data->scale.y / 5;

	if(z && direction)
		data->scale.z += data->scale.z / 5;
	if(z && !direction)
		data->scale.z -= data->scale.z / 5;
	if(data->scale.x <= 0.00000000000f || data->scale.y <= 0.00000000000f || data->scale.z <= 0.00000000000f)
		data->scale = (t_point){0.0f, 0.0f, 0.0f, 1.0f};
	return 0;
}


void animate(t_loop_data *data)
{
	if(data->animate)
	{
		rotate(data, 1, 0, 1, data->anim_dir);
	}
	
}


typedef struct {
	t_loop_data *mlx;
	t_main *m;
}t_all;

int	loop(t_all *data)
{
	(void)data;
	animate(data->mlx);
	clear_img(data->mlx);
	draw(*data->mlx, *data->m);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->img.img, 0, 0);

	return 0;
}

void init(t_loop_data *mlx, t_main *m, int map)
{
	t_point *result = get_split_fdf(map, &m->size, &m->i_i, &m->j_j);
	mlx->result = result;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 1920, 1080, "FDF");
	mlx->img.img = mlx_new_image(mlx->mlx, 1920, 1080);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length,
								&mlx->img.endian);
	mlx_hook(mlx->mlx_win, 17, 0L, close, mlx);
	mlx_hook(mlx->mlx_win, 2, 1L<<0, handle_keys, mlx);
	
}

int main(int argnum, char **args)
{
	(void)(argnum);
	int map = open(args[1], O_RDONLY);
	t_main m = {0};
	t_loop_data mlx = {0};
	init(&mlx, &m, map);
	get_matrix(&mlx, m);
	m.i = 1;
	draw(mlx, m);	
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
	mlx_loop_hook(mlx.mlx, loop, (t_all[]){{&mlx, &m}});
	mlx_loop(mlx.mlx);
	return 0;
}