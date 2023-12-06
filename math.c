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

(x*a + y*b + z*c + w*d;
 x*e + y*f + z*g + w*h;
 x*i + y*j + z*k + w*l;
 x*m + y*n + z*o + w*p)
}