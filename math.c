/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:45:53 by amajid            #+#    #+#             */
/*   Updated: 2023/12/22 22:20:31 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_matrix4f	get_identity_matrix(void)
{
	return ((t_matrix4f){.m[0][0] = 1.0f, .m[1][0] = 0.0f,
		.m[2][0] = 0.0f, .m[3][0] = 0.0f,
		.m[0][1] = 0.0f, .m[1][1] = 1.0f,
		.m[2][1] = 0.0f, .m[3][1] = 0.0f,
		.m[0][2] = 0.0f, .m[1][2] = 0.0f,
		.m[2][2] = 1.0f, .m[3][2] = 0.0f,
		.m[0][3] = 0.0f, .m[1][3] = 0.0f,
		.m[2][3] = 0.0f, .m[3][3] = 1.0f});
}

// left = x, right = y, bottom = z, top = w;

t_matrix4f	orthogonal(t_point m, float near, float far)
{
	t_matrix4f	matrix;

	matrix = get_identity_matrix();
	matrix.m[0][0] = 2 / (m.y - m.x);
	matrix.m[1][1] = 2 / (m.w - m.z);
	matrix.m[2][2] = -2 / (far - near);
	matrix.m[3][2] = (far + near) / (far - near);
	matrix.m[3][0] = (m.y + m.x) / (m.y - m.x);
	matrix.m[3][1] = (m.w + m.z) / (m.w - m.z);
	return (matrix);
}

t_point	point_matrix_multiply(t_matrix4f m, t_point v)
{
	t_point	result;

	result = (t_point){v.x * m.m[0][0] + v.y * m.m[1][0]
		+ v.z * m.m[2][0] + v.w * m.m[3][0],
		v.x * m.m[0][1] + v.y * m.m[1][1]
		+ v.z * m.m[2][1] + v.w * m.m[3][1],
		v.x * m.m[0][2] + v.y * m.m[1][2]
		+ v.z * m.m[2][2] + v.w * m.m[3][2],
		v.x * m.m[0][3] + v.y * m.m[1][3]
		+ v.z * m.m[2][3] + v.w * m.m[3][3]};
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

t_matrix4f	matrix4x4_set_rotation_x(float flAngle)
{
	t_matrix4f	result;
	
	result = get_identity_matrix();
	flAngle = (flAngle * M_PI / 180);
	result.m[1][1] = cos(flAngle);
	result.m[2][1] = -sin(flAngle);
	result.m[1][2] = sin(flAngle);
	result.m[2][2] = cos(flAngle);
	return (result);
}

t_matrix4f	matrix4x4_set_rotation_y(float flAngle)
{
	t_matrix4f	result;
	
	result = get_identity_matrix();
	flAngle = (flAngle * M_PI / 180);
	result.m[0][0] = cos(flAngle);
	result.m[2][0] = sin(flAngle);
	result.m[0][2] = -sin(flAngle);
	result.m[2][2] = cos(flAngle);
	return (result);
}

t_matrix4f	matrix4x4_set_rotation_z(float flAngle)
{
	t_matrix4f	result;
	
	result = get_identity_matrix();
	flAngle = (flAngle * M_PI / 180);
	result.m[0][0] = cos(flAngle);
	result.m[1][0] = -sin(flAngle);
	result.m[0][1] = sin(flAngle);
	result.m[1][1] = cos(flAngle);
	return (result);
}


t_point	matrix4x4_set_rotation(float flAngle, t_point axis, t_point v)
{
	t_point result;

	result = v;
	if(axis.x == 1.0f)
		result = point_matrix_multiply(matrix4x4_set_rotation_x(flAngle), result);
	if(axis.y == 1.0f)
		result = point_matrix_multiply(matrix4x4_set_rotation_y(flAngle), result);
	if(axis.z == 1.0f)
		result = point_matrix_multiply(matrix4x4_set_rotation_z(flAngle), result);
	return result;
}




