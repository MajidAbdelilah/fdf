#pragma once

#define Z_DIVE 8
#define XYZ_MUL 16

typedef struct 
{
	// RIGHT
	float	x;
	// FORWARD
	float	y;
	// UP
	float	z;
	float	w;
}	t_point;

typedef struct 
{
	float m[4][4];
}t_matrix4f;

#define IDENTITY_MATRIX (t_matrix4f){.m[0][0] = 1.0f, .m[1][0] = 1.0f, .m[2][0] = 1.0f, .m[3][0] = 1.0f, \
									.m[0][1] = 1.0f, .m[1][1] = 1.0f, .m[2][1] = 1.0f, .m[3][1] = 1.0f, \
									.m[0][2] = 1.0f, .m[1][2] = 1.0f, .m[2][2] = 1.0f, .m[3][2] = 1.0f, \
									.m[0][3] = 1.0f, .m[1][3] = 1.0f, .m[2][3] = 1.0f, .m[3][3] = 1.0f}

typedef struct
{
	t_point v[4];
} t_quad;

t_point	*get_split_fdf(int fd, unsigned int *size);
