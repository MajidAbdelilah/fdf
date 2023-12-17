#pragma once

#define Z_DIVE 8
#define XYZ_MUL 4

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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct 
{
	t_point Position;
	t_point Target;
} t_camera;
typedef struct
{
	t_point *Vertices; 
    t_point Position;
	t_point Rotation;
} t_mesh;
#define IDENTITY_MATRIX (t_matrix4f){.m[0][0] = 1.0f, .m[1][0] = 0.0f, .m[2][0] = 0.0f, .m[3][0] = 0.0f, \
									.m[0][1] = 0.0f, .m[1][1] = 1.0f, .m[2][1] = 0.0f, .m[3][1] = 0.0f, \
									.m[0][2] = 0.0f, .m[1][2] = 0.0f, .m[2][2] = 1.0f, .m[3][2] = 0.0f, \
									.m[0][3] = 0.0f, .m[1][3] = 0.0f, .m[2][3] = 0.0f, .m[3][3] = 1.0f}

typedef struct
{
	t_point v[4];
} t_quad;


typedef struct {
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point *result;
	t_matrix4f model;
	t_point rotation;
	t_matrix4f pers;
} t_loop_data;
typedef struct {
unsigned int size;
	unsigned int j_j;
	unsigned int i_i;
	unsigned int i;
	unsigned int i_size;
	unsigned int j;
	unsigned int last_line_index;
	char up;
	int x_min;
	int y_min;

} t_main;

t_point	*get_split_fdf(int fd, unsigned int *size, unsigned int *size_i, unsigned int *size_j);
t_matrix4f perspective(float left,float right,float bottom,float top,float near,float far);
t_matrix4f orthogonal(float left,float right,float bottom,float top,float near,float far);
t_point point_matrix_multiply (t_matrix4f m, t_point v);
t_point get_normalized_ray(t_point p1, t_point p2);
void DDA(float X0, float Y0, float X1, float Y1, t_data *data, int color);
int get_max(int x, int y);
int get_min(int x, int y);
t_matrix4f matrix4x4_set_scale(t_point vecScale);
t_matrix4f matrix4x4_set_rotation(float flAngle, t_point v);
t_matrix4f matrix4x4_set_translation(t_point vecPos);
t_matrix4f Matrix4x4_mul(t_matrix4f left, t_matrix4f right);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_matrix4f get_isometric_matrix();


void get_matrix(t_loop_data *mlx, t_main m);
float get_scale(t_loop_data d, t_main *m, t_matrix4f rotation, t_matrix4f pers);
void draw(t_loop_data d, t_main m);
int	esc_close(int keycode, t_loop_data *vars);
int	close(t_loop_data *vars);
