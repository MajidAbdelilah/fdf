/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:45:53 by amajid            #+#    #+#             */
/*   Updated: 2023/12/20 18:11:53 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_matrix4f	get_identity_matrix()
{
	return ((t_matrix4f){.m[0][0] = 1.0f, .m[1][0] = 0.0f, .m[2][0] = 0.0f, .m[3][0] = 0.0f,
							.m[0][1] = 0.0f, .m[1][1] = 1.0f, .m[2][1] = 0.0f, .m[3][1] = 0.0f,
							.m[0][2] = 0.0f, .m[1][2] = 0.0f, .m[2][2] = 1.0f, .m[3][2] = 0.0f,
							.m[0][3] = 0.0f, .m[1][3] = 0.0f, .m[2][3] = 0.0f, .m[3][3] = 1.0f});
}

t_matrix4f	orthogonal(float left,float right,float bottom,float top,float near,float far)
{
	t_matrix4f	matrix;

	matrix = get_identity_matrix();
	matrix.m[0][0] = 2/(right - left);
	matrix.m[1][1] = 2/(top - bottom);
	matrix.m[2][2] = -2/(far - near);
	matrix.m[3][2] = (far+near)/(far - near);
	matrix.m[3][0] = (right+left)/(right -left);
	matrix.m[3][1] = (top + bottom)/(top-bottom);
	return (matrix);
}

t_point	point_matrix_multiply(t_matrix4f m, t_point v)
{
	t_point result;

	result = (t_point){v.x*m.m[0][0] + v.y*m.m[1][0] + v.z*m.m[2][0] + v.w*m.m[3][0],
 					v.x*m.m[0][1] + v.y*m.m[1][1] + v.z*m.m[2][1] + v.w*m.m[3][1],
					v.x*m.m[0][2] + v.y*m.m[1][2] + v.z*m.m[2][2] + v.w*m.m[3][2],
					v.x*m.m[0][3] + v.y*m.m[1][3] + v.z*m.m[2][3] + v.w*m.m[3][3]};
 return (result);
}

t_matrix4f	matrix4x4_set_scale(t_point vecScale)
{
	t_matrix4f	result;

	result = get_identity_matrix();
	result.m[0][0] = vecScale.x;
	result.m[1][1] = vecScale.y;
	result.m[2][2] = vecScale.z;
	return (result);
}

// Normalize beforehand
// c = cos(angle), s = sin(angle), t = (1-c)
// [ xxt+c   xyt-zs  xzt+ys ]
// [ yxt+zs  yyt+c   yzt-xs ]
// [ zxt-ys  zyt+xs  zzt+c  ]

t_matrix4f	matrix4x4_set_rotation(float flAngle, t_point v)
{
	t_matrix4f result;

	result = get_identity_matrix();
	v.x *= v.x;
	v.y *= v.y;
	v.z *= v.z;
	float x = v.x;
	float y = v.y;
	float z = v.z;
	float c = cos(flAngle*M_PI/180);
	float s = sin(flAngle*M_PI/180);
	float t = 1-c;
	result.m[0][0] = x * x * t + c;
	result.m[1][0] = x * y * t - z * s;
	result.m[2][0] = x * z * t + y * s;
	result.m[0][1] = y * x * t + z * s;
	result.m[1][1] = y * y * t + c;
	result.m[2][1] = y * z * t - x * s;
	result.m[0][2] = z * x * t - y * s;
	result.m[1][2] = z * y * t + x * s;
	result.m[2][2] = z * z * t + c;
	return (result);
}

t_matrix4f	matrix4x4_set_translation(t_point vecPos)
{
	t_matrix4f	result;

	result = get_identity_matrix();
	result.m[3][0] = vecPos.x;
	result.m[3][1] = vecPos.y;
	result.m[3][2] = vecPos.z;
	return (result);
}

// [a b c d][A B C D]   [aA+bE+cI+dM
// [e f g h][E F G H] = [eA+fE+gI+hM ...
// [i j k l][I J K L]
// [m n o p][M N O P]

t_matrix4f	Matrix4x4_mul(t_matrix4f left, t_matrix4f right)
{
	t_matrix4f result;
	
	result = get_identity_matrix();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			result.m[i][j] = left.m[0][j]*right.m[i][0] + left.m[1][j]*right.m[i][1] + left.m[2][j]*right.m[i][2] + left.m[3][j]*right.m[i][3];
	}

	return (result);
}

float	my_abs(float n)
{
	return ((n > 0.0f) ? n : (n * (-1.0f)));
} 

int	my_abs_int(int n)
{ 
	return ((n > 0) ? n : (n * (-1)));
} 

int	get_max(int x, int y)
{
	char is_x;
	
	is_x = (x > y);
	return (x * is_x + y * !is_x);
}

int get_min(int x, int y)
{
	char is_x;
	
	is_x = (x < y);
	return (x * is_x + y * !is_x);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	DDA(float X0, float Y0, float X1, float Y1, t_data *data, int color) 
{ 
	float		steps;
	t_point		dda;
	long long	i;
	char		is_x;

	dda.x = X1 - X0;
	dda.y = Y1 - Y0;
	is_x = my_abs(dda.x) > my_abs(dda.y);
	steps = is_x * my_abs(dda.x) + my_abs(dda.y) * !is_x;
	dda.z = dda.x / (float)steps;
	dda.w = dda.y / (float)steps;
	i = -2;
	while (++i <= steps)
	{
		if (X0 > (W - 10) || X0 < 10 || Y0 > (H - 10) || Y0 < 10)
		{
			X0 += dda.z;
			Y0 += dda.w;
			continue ;
		}
		my_mlx_pixel_put(data, round(X0), round(Y0), color);
		X0 += dda.z;
		Y0 += dda.w;
	}
}
