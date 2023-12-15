#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include "mlx/mlx.h"




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
		printf("%u(x = %f, y = %f, z = %f, w = %f)\n", i, result[i].x, result[i].y, result[i].z, result[i].w);
		i++;
		if(result[i].x == 0.0f)
			printf("\n");
	}

	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
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

	int x_max = 0;
	int x_min = 0;
	int y_max = 0;
	int y_min = 0;
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

	float scale_x = (float)(1920 - 300) / (abs(x_max) + abs(x_min));
	float scale_y = (float)(1080 - 300) / (abs(y_max) + abs(y_min));
	float scale = (scale_x < scale_y) * scale_x + !(scale_x < scale_y) * scale_y;
	printf("(x_max + x_min) * scale_x = %d\n", (abs(x_max) + abs(x_min)));
	printf("(y_max + y_min) * scale_y = %d\n", (abs(y_max) + abs(y_min)));
	
	model = Matrix4x4_mul(matrix4x4_set_translation((t_point){ (float)(1920 - ((float)(abs(x_max) + abs(x_min)) / 2) * scale) / 2 + 70, (float)(1080 - ((float)(abs(y_max) + abs(y_min)) / 2) * scale) / 2 - 70, 900.0f, 0}), Matrix4x4_mul(rotation, matrix4x4_set_scale((t_point){scale, scale, scale, 1.0f})));
	i = 1;
	while(i < (size))
	{
		//printf("%u(x = %f, y = %f, z = %f)\n", i, result[i].x, result[i].y, result[i].z);
		t_point p = result[i];
		p = point_matrix_multiply(model, p);
		p = point_matrix_multiply(pers, p);
	
		
		t_point p2;
		// p2.x = (p2.x / p2.w) / 2;
		// p2.y = (p2.y / p2.w) / 2;
		 printf("kh 0= %u(x = %f, y = %f, z = %f, w = %f)\n", i, p.x, p.y, p.z, p.w);
		// p.x *= ((float)1920/2);
		// p.y *= ((float)1080/2);
			
		
		if((i % i_i) == 0)
		{
			i_size = last_line_index;
			last_line_index = i;
			j = 0;
			up = 1;
			printf("\n");
		}else {
			p2 = result[i-1];
			p2 = point_matrix_multiply(model, p2);
			p2 = point_matrix_multiply(pers, p2);
			 printf("kh 1= %u(x = %f, y = %f, z = %f, w = %f)\n", i, p2.x, p2.y, p2.z, p2.w);
			if(result[i].y < 0.0f || result[i-1].y < 0.0f)
				DDA(p.x, p.y, p2.x, p2.y, &img, 0x00990000);
			else
			 	DDA(p.x, p.y, p2.x, p2.y, &img, 0x00000099);
			my_mlx_pixel_put(&img, p2.x, p2.y, 0x00009900);

		}
		if(up)
		{
			p2 = result[i - i_i];
			p2 = point_matrix_multiply(model, p2);
			p2 = point_matrix_multiply(pers, p2);
			 printf("kh 2= %u(x = %f, y = %f, z = %f, w = %f)\n", i, p2.x, p2.y, p2.z, p2.w);
			if(result[i].y < 0.0f || result[i - i_i].y < 0.0f)
				DDA(p.x, p.y, p2.x, p2.y, &img, 0x00990000);
			else
				DDA(p.x, p.y, p2.x, p2.y, &img, 0x00000099);
			my_mlx_pixel_put(&img, p2.x, p2.y, 0x00009900);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	printf("kjbkcbsdkbcksdbcdkjbcskjbcdksjbcksdjbcksb\n");
	mlx_loop(mlx);
	return 0;
}