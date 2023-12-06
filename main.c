#include "fdf.h"
#include <fcntl.h>
#include <sys/fcntl.h>
#include "ft_printf/ft_printf.h"
#include <stdio.h>

int main()
{
	int map = open("../test_maps/42.fdf", O_RDONLY);
	unsigned int size = 0;
	t_point *result = get_split_fdf(map, &size);
	unsigned int i = 0;
	while(i < (size + 100))
	{
		printf("%u(x = %f, y = %f, z = %f)\n", i, result[i].x, result[i].y, result[i].z);
		i++;
		if(result[i].x == 0.0f)
			printf("\n");
	}
	void	*mlx;

	mlx = mlx_init();
	return 0;
}