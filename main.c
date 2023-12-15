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
	i = 1;
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

	model = Matrix4x4_mul(matrix4x4_set_translation((t_point){600.0f, 150.0f, -0.0f, 0}), Matrix4x4_mul(rotation, matrix4x4_set_scale((t_point){0.65f, 0.65f, 0.65f, 1.0f})));
//	t_matrix4f iso = get_isometric_matrix();
	unsigned int j = 0;
	unsigned int last_line_index = 0;
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
			my_mlx_pixel_put(&img, p2.x, p2.y, 0x00009999);

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
			my_mlx_pixel_put(&img, p2.x, p2.y, 0x00009999);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	printf("kjbkcbsdkbcksdbcdkjbcskjbcdksjbcksdjbcksb\n");
	mlx_loop(mlx);
	return 0;
}