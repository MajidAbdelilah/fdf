#include "fdf.h"
#include <math.h>

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
t_matrix4f orthogonal(float left,float right,float bottom,float top,float near,float far)
{
	t_matrix4f matrix = IDENTITY_MATRIX;


	matrix.m[0][0] = 2/(right - left);
	matrix.m[1][1] = 2/(top - bottom);
	matrix.m[2][2] = -2/(far - near);
	matrix.m[3][2] = (far+near)/(far - near);
	matrix.m[3][0] = (right+left)/(right -left);
	matrix.m[3][1] = (top + bottom)/(top-bottom);

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
t_matrix4f matrix4x4_set_scale(t_point vecScale)
{
	t_matrix4f result = IDENTITY_MATRIX;
	result.m[0][0] = vecScale.x;
	result.m[1][1] = vecScale.y;
	result.m[2][2] = vecScale.z;
	return result;
}
t_matrix4f matrix4x4_set_rotation(float flAngle, t_point v)
{
	t_matrix4f result = IDENTITY_MATRIX;
	// Normalize beforehand
	v = (t_point){v.x * v.x, v.y * v.y, v.z * v.z, v.w};

	// c = cos(angle), s = sin(angle), t = (1-c)
	// [ xxt+c   xyt-zs  xzt+ys ]
	// [ yxt+zs  yyt+c   yzt-xs ]
	// [ zxt-ys  zyt+xs  zzt+c  ]

	float x = v.x;
	float y = v.y;
	float z = v.z;

	float c = cos(flAngle*M_PI/180);
	float s = sin(flAngle*M_PI/180);
	float t = 1-c;

	result.m[0][0] = x*x*t + c;
	result.m[1][0] = x*y*t - z*s;
	result.m[2][0] = x*z*t + y*s;

	result.m[0][1] = y*x*t + z*s;
	result.m[1][1] = y*y*t + c;
	result.m[2][1] = y*z*t - x*s;

	result.m[0][2] = z*x*t - y*s;
	result.m[1][2] = z*y*t + x*s;
	result.m[2][2] = z*z*t + c;

	return result;
}

t_matrix4f matrix4x4_set_translation(t_point vecPos)
{
	t_matrix4f result = IDENTITY_MATRIX;
	result.m[3][0] = vecPos.x;
	result.m[3][1] = vecPos.y;
	result.m[3][2] = vecPos.z;
	return result;
}

t_matrix4f Matrix4x4_mul(t_matrix4f left, t_matrix4f right)
{
	// [a b c d][A B C D]   [aA+bE+cI+dM
	// [e f g h][E F G H] = [eA+fE+gI+hM ...
	// [i j k l][I J K L]
	// [m n o p][M N O P]
	t_matrix4f result = IDENTITY_MATRIX;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			result.m[i][j] = left.m[0][j]*right.m[i][0] + left.m[1][j]*right.m[i][1] + left.m[2][j]*right.m[i][2] + left.m[3][j]*right.m[i][3];
	}

	return result;
}

float my_abs(float n) { return ((n > 0.0f) ? n : (n * (-1.0f))); } 
int get_max(int x, int y)
{
	char is_x = (x > y);
	return (x * is_x + y * !is_x);
}
int get_min(int x, int y)
{
	char is_x = (x < y);
	return (x * is_x + y * !is_x);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void DDA(float X0, float Y0, float X1, float Y1, t_data *data, int color) 
{ 
    // calculate dx & dy 
    float dx = X1 - X0; 
    float dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    float steps = my_abs(dx) > my_abs(dy) ? my_abs(dx) : my_abs(dy); 
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
        my_mlx_pixel_put(data, round(X), round(Y), 
                 color); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
    } 
} 

t_matrix4f get_isometric_matrix()
{
	t_matrix4f result = IDENTITY_MATRIX;
	float xAxis = M_PI * ( (float)1 /  4);
	result.m[0][0] = cos(xAxis);
	result.m[0][1] = sin(xAxis); 
	result.m[0][2] = 0;

	float yAxis = M_PI * ( (float)4 / 6);
	result.m[1][0] = cos(yAxis); 
	result.m[1][1] = sin(yAxis); 
	result.m[1][2] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = -1;
	result.m[2][2] = 0;

	return result;
}