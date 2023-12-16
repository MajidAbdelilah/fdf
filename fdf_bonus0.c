#include "fdf.h"

int rotate(t_loop_data *data, char x, char y, char z, char direction)
{
	if(x && direction)
		data->rotation.x += 0.0000001;
	if(x && !direction)
		data->rotation.x -= 0.0000001;

	if(y && direction)
		data->rotation.y += 0.0000001;
	if(y && !direction)
		data->rotation.y -= 0.0000001;

	if(z && direction)
		data->rotation.z += 0.0000001;
	if(z && !direction)
		data->rotation.z -= 0.0000001;
	return 0;
}

int	loop(void *data)
{
	(void)data;
	

	return 0;
}

int main(int argnum, char **args)
{
	
}