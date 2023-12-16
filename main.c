#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include "mlx/mlx.h"

typedef struct {
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point *result;
} t_loop_data;

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

int main(int argnum, char **args)
{
	(void)(argnum);
	int map = open(args[1], O_RDONLY);
	unsigned int size = 0;
	unsigned int j_j = 0;
	unsigned int i_i = 0;
	t_point *result = get_split_fdf(map, &size, &i_i, &j_j);
	unsigned int i = 0;
	while(i < (size))
	{
		////printf("%u(x = %f, y = %f, z = %f, w = %f)\n", i, result[i].x, result[i].y, result[i].z, result[i].w);
		i++;
		//if(result[i].x == 0.0f)
			//printf("\n");
	}
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
	unsigned int i_size = 0;
	char up = 0;

	t_matrix4f model = IDENTITY_MATRIX;
	t_matrix4f rotation = IDENTITY_MATRIX;
	//   rotation = matrix4x4_set_rotation( 180, (t_point){0.0f,1.0f,0.0f, 0.0f});
	//   rotation = matrix4x4_set_rotation( 180, (t_point){1.0f,0.0f,0.0f, 0.0f});
	//  rotation = matrix4x4_set_rotation( 0, (t_point){0.0f,0.0f,1.0f, 0.0f});
	
	
	rotation = Matrix4x4_mul(matrix4x4_set_rotation(-45, (t_point){0.0f,1.0f,0.0f, 0.0f}), rotation);
	rotation = Matrix4x4_mul(matrix4x4_set_rotation(-35, (t_point){1.0f,0.0f,0.0f, 0.0f}), rotation);

//	t_matrix4f iso = get_isometric_matrix();
	unsigned int j = 0;
	unsigned int last_line_index = 0;


	t_point p = result[0];
	p = point_matrix_multiply(rotation, p);
	p = point_matrix_multiply(pers, p);
	int x_max = p.x;
	int x_min = p.x;
	int y_max = p.y;
	int y_min = p.y;
	i = 0;
	while(i < size)
	{
		t_point p = result[i];
		p = point_matrix_multiply(rotation, p);
		p = point_matrix_multiply(pers, p);
		x_max = get_max(x_max, p.x);
		y_max = get_max(y_max, p.y);
		x_min = get_min(x_min, p.x);
		y_min = get_min(y_min, p.y);
		i++;
	}

	float scale_x = (float)(1920 - 400) / (abs(x_max) + abs(x_min));
	float scale_y = (float)(1080 - 400) / (abs(y_max) + abs(y_min));
	float scale = (scale_x < scale_y) * scale_x + !(scale_x < scale_y) * scale_y;
	////printf("(x_max + x_min) * scale_x = %d\n", (abs(x_max) + abs(x_min)));
	////printf("(y_max + y_min) * scale_y = %f\n", scale);
	
	model = Matrix4x4_mul(matrix4x4_set_translation((t_point){ abs(x_min) * scale + 30, (abs(y_min) * scale) + 30, 0.0f, 0}), Matrix4x4_mul(rotation, matrix4x4_set_scale((t_point){scale, scale, scale, 1.0f})));
	i = 1;
	while(i < (size))
	{
		//////printf("%u(x = %f, y = %f, z = %f)\n", i, result[i].x, result[i].y, result[i].z);
		t_point p = result[i];
		p = point_matrix_multiply(model, p);
		p = point_matrix_multiply(pers, p);
	
		
		t_point p2;
		// p2.x = (p2.x / p2.w) / 2;
		// p2.y = (p2.y / p2.w) / 2;
		 ////printf("kh 0= %u(x = %f, y = %f, z = %f, w = %f)\n", i, p.x, p.y, p.z, p.w);
		// p.x *= ((float)1920/2);
		// p.y *= ((float)1080/2);
			
		
		if((i % i_i) == 0)
		{
			i_size = last_line_index;
			last_line_index = i;
			j = 0;
			up = 1;
			////printf("\n");
		}else {
			p2 = result[i-1];
			p2 = point_matrix_multiply(model, p2);
			p2 = point_matrix_multiply(pers, p2);
			 //printf("kh 1= %u(x = %f, y = %f, z = %f, w = %f)\n", i, p2.x, p2.y, p2.z, p2.w);
			if(p2.x > 1920 || p2.x < 0 || p2.y > 1080 || p2.y < 0 || p.x > 1920 || p.x < 0 || p.y > 1080 || p.y < 0)
				{
					i++;
					continue;
				}
			if(result[i].y < 0.0f || result[i-1].y < 0.0f)
				DDA(p.x, p.y, p2.x, p2.y, &mlx.img, 0x00990000);
			else
			 	DDA(p.x, p.y, p2.x, p2.y, &mlx.img, 0x00000099);
			my_mlx_pixel_put(&mlx.img, p2.x, p2.y, 0x00009900);

		}
		if(up)
		{
			p2 = result[i - i_i];
			p2 = point_matrix_multiply(model, p2);
			p2 = point_matrix_multiply(pers, p2);
			 //printf("kh 2= %u(x = %f, y = %f, z = %f, w = %f)\n", i, p2.x, p2.y, p2.z, p2.w);
			if(p2.x > 1920 || p2.x < 0 || p2.y > 1080 || p2.y < 0 || p.x > 1920 || p.x < 0 || p.y > 1080 || p.y < 0)
				{
					i++;
					continue;
				}
			if(result[i].y < 0.0f || result[i - i_i].y < 0.0f)
				DDA(p.x, p.y, p2.x, p2.y, &mlx.img, 0x00990000);
			else
				DDA(p.x, p.y, p2.x, p2.y, &mlx.img, 0x00000099);
			my_mlx_pixel_put(&mlx.img, p2.x, p2.y, 0x00009900);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
	//printf("kjbkcbsdkbcksdbcdkjbcskjbcdksjbcksdjbcksb\n");
	mlx_loop_hook(mlx.mlx, loop, 0);

	mlx_loop(mlx.mlx);
	return 0;
}