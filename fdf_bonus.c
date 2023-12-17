#include "fdf.h"
#include <sys/fcntl.h>
#include "mlx.h"
#include <stdio.h>
int rotate(t_loop_data *data, char x, char y, char z, char direction)
{
	if(x && direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(1, (t_point){1.0f, 0.0f,  0.0f,  0.0f}), data->rotation);
	if(x && !direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(-1, (t_point){1.0f, 0.0f,  0.0f,  0.0f}), data->rotation);

	if(y && direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(1, (t_point){0.0f, 1.0f,  0.0f,  0.0f}), data->rotation);
	if(y && !direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(-1, (t_point){0.0f, 1.0f,  0.0f,  0.0f}), data->rotation);

	if(z && direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(1, (t_point){0.0f, 0.0f,  1.0f,  0.0f}), data->rotation);
	if(z && !direction)
		data->rotation = Matrix4x4_mul(matrix4x4_set_rotation(-1, (t_point){0.0f, 0.0f,  1.0f,  0.0f}), data->rotation);
	return 0;
}
typedef struct {
	t_loop_data *mlx;
	t_main *m;
}t_all;

int	loop(t_all *data)
{
	(void)data;
	
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