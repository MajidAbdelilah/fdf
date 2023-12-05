#pragma once

#define Z_DIVE 8

typedef struct 
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct
{
	t_point v[4];
} t_quad;