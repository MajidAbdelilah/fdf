#include "fdf.h"

void clear_img(t_loop_data *mlx)
{
	int i = 0;
	while(i < 1080)
	{
		int j = 0;
		while(j < 1920)
		{
			my_mlx_pixel_put(&mlx->img, j, i, 0x00000000);
			j++;
		}
		i++;
	}
}

void draw(t_loop_data d, t_main m)
{
	d.model =  Matrix4x4_mul(matrix4x4_set_translation(d.transition), Matrix4x4_mul(d.rotation, matrix4x4_set_scale((t_point){d.scale.x, d.scale.y, d.scale.z, 1.0f})));
while(m.i < (m.size))
	{
		t_point p = d.result[m.i];
		p = point_matrix_multiply(d.model, p);
		p = point_matrix_multiply(d.pers, p);		
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
			p2 = point_matrix_multiply(d.pers, p2);
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
			p2 = point_matrix_multiply(d.pers, p2);
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
