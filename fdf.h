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
}	t_point;

typedef struct
{
	t_point v[4];
} t_quad;

t_point	*get_split_fdf(int fd, unsigned int *size);
