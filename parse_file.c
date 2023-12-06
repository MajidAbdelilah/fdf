#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include "gnl/gnl.h"
#include "fdf.h"
#include <stdlib.h>

t_point	get_point(int x, int y, int z)
{
	t_point result;

	result.x = x * XYZ_MUL;
	result.y = y * XYZ_MUL;
	result.z = ((float)z * XYZ_MUL) / Z_DIVE;
	return result;
}

void adjust_result_size(t_point *result, unsigned int *size){
	t_point	*tmp;
	int		mul;

	mul = 3;
	tmp = malloc(sizeof(t_point) * (*size));
	ft_memcpy(tmp, result, sizeof(t_point) * (*size));
	free(result);
	result = malloc(sizeof(t_point) * ((*size) * mul));
	ft_memcpy(result, tmp, sizeof(t_point) * (*size));
	free(tmp);
	(*size) *= mul;
}

t_point	*get_split_fdf(int fd, int *size)
{
	unsigned int	r_size;
	unsigned int	i;
	unsigned int	j;
	unsigned int	atoi_ret;
	unsigned int	index;
	t_point *result;
	
	r_size = 100000;
	result = malloc(sizeof(t_point) * r_size);
	j = 0;
	index = 0;
	while(1)
	{
		char *line = get_next_line(fd);
		if(!line)
			break;
		char **splited_line = ft_split(line, ' ');
		if(!splited_line)
			return NULL;
		i = 0;
		while(splited_line[i])
		{
			if(index >= (r_size - 1))
				adjust_result_size(result, &r_size);
			result[index++] = get_point(i, j, ft_atoi(splited_line[i]));
			i++;
		}
		j++;
	}
	(*size) = index;
	return result;
}