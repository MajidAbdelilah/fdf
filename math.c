#include "fdf.h"

t_matrix4f perspective(float left,float right,float bottom,float top,float near,float far)
{
	t_matrix4f matrix;

	matrix = IDENTITY_MATRIX;
	matrix.m[0][0] = 2*near/(right - left);
	matrix.m[1][1] = 2*near/(top - bottom);
	matrix.m[2][2] = -(far +near)/(far - near);
	matrix.m[2][3] = -1;
	matrix.m[3][2] = -2*far*near/(far - near);
	matrix.m[2][0] = (right+left)/(right -left);
	matrix.m[2][1] = (top + bottom)/(top-bottom);
	matrix.m[3][3] = 0;
	return matrix;
}


t_point point_matrix_multiply (t_matrix4f m, t_point v)
{
	t_point result;

	result = (t_point){v.x*m.m[0][0] + v.y*m.m[1][0] + v.z*m.m[2][0] + v.w*m.m[3][0],
 					v.x*m.m[0][1] + v.y*m.m[1][1] + v.z*m.m[2][1] + v.w*m.m[3][1],
					v.x*m.m[0][2] + v.y*m.m[1][2] + v.z*m.m[2][2] + v.w*m.m[3][2],
					v.x*m.m[0][3] + v.y*m.m[1][3] + v.z*m.m[2][3] + v.w*m.m[3][3]};
 
 return result;
}