#include "fdf.h"
#include <stdio.h>
#include "mlx.h"
#include <stdlib.h>
int	handle_keys(int keycode, t_loop_data *vars)
{
	// if(keycode != 53)
	// 	return 0;
	(void)vars;
	printf("keycode = %d\n", keycode);
	if(keycode == 31)
		rotate(vars, 1, 0, 0, 0);
	if(keycode == 37)
		rotate(vars, 1, 0, 0, 1);
	if(keycode == 34)
		rotate(vars, 0, 1, 0, 0);
	if(keycode == 40)
		rotate(vars, 0, 1, 0, 1);
	if(keycode == 32)
		rotate(vars, 0, 0, 1, 0);
	if(keycode == 38)
		rotate(vars, 0, 0, 1, 1);
	
	if(keycode == 12)
		translate(vars, 1, 0, 0, 0);
	if(keycode == 0)
		translate(vars, 1, 0, 0, 1);
	if(keycode == 13)
		translate(vars, 0, 1, 0, 0);
	if(keycode == 1)
		translate(vars, 0, 1, 0, 1);

	if(keycode == 78)
		scale(vars, 1, 1, 1, 0);
	if(keycode == 69)
		scale(vars, 1, 1, 1, 1);

	if(keycode == 7)
		vars->animate = !vars->animate;

	if(keycode == 6)
		Multiview_orthographic_projection(vars);



	if(keycode != 53)
		return 0;
	
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	
	free(vars->result);
	free(vars->mlx);
	//free(vars->img.addr);
	exit(0);
	//vars->mlx = 0;
	//vars->mlx_win = 0;
	return (0);
}