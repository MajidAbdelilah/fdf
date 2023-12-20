#include "fdf.h"
#include "/usr/local/include/mlx.h"
#include <stdlib.h>
int	mlx_close(t_loop_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	
	free(vars->result);
	//free(vars->mlx);
	//free(vars->result);
	//free(vars->img.addr);

	exit(0);
	//vars->mlx = 0;
	//vars->mlx_win = 0;
	
	return (0);
}

int	esc_close(int keycode, t_loop_data *vars)
{
	if(keycode != 53)
		return 0;
	
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	
	free(vars->result);
	//free(vars->mlx);
	//free(vars->img.addr);
	exit(0);
	//vars->mlx = 0;
	//vars->mlx_win = 0;
	return (0);
}