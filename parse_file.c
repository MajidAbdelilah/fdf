#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include "gnl/gnl.h"
#include "fdf.h"
#include <stdlib.h>

t_point	get_point(int x, int y, int z)
{
	t_point result;

	result.x = x * XYZ_MUL;
	result.z = y * XYZ_MUL;
	result.y = -((float)z * XYZ_MUL);
	result.w = 1.0f;
	return result;
}

void adjust_result_size(t_point **result, unsigned int *size){
	t_point	*tmp;
	int		mul;

	mul = 3;
	tmp = malloc(sizeof(t_point) * (*size));
	ft_memcpy(tmp, *result, sizeof(t_point) * (*size));
	free(*result);
	*result = malloc(sizeof(t_point) * ((*size) * mul));
	ft_memcpy(*result, tmp, sizeof(t_point) * (*size));
	free(tmp);
	(*size) *= mul;
}


void fix_positions(t_point *data, unsigned int size, unsigned int i_i, unsigned int j_j)
{
	int max = 0;
	int min = 0;
	int avg = 0;
	unsigned int i = 0;
	while(i < size)
	{
		max = get_max(max, data[i].y);
		min = get_min(min, data[i].y);
		i++;
	}
	i = 0;
	avg = max + min;
	while(i < size)
	{
		data[i].y -= (float)(avg) / 2;
		data[i].x -= (float)(i_i * XYZ_MUL) / 2;
		data[i].z -= (float)(j_j * XYZ_MUL) / 2;
		i++;
	}
}

t_point	*get_split_fdf(int fd, unsigned int *size, unsigned int *size_i, unsigned int *size_j)
{
	unsigned int	r_size;
	unsigned int	i;
	unsigned int	j;
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
				adjust_result_size(&result, &r_size);
			result[index++] = get_point(i, j, ft_atoi(splited_line[i]));
			i++;
		}
		j++;
	}
	fix_positions(result, index, i - 1, j - 1);
	*size_i = i;
	*size_j = j;
	(*size) = index;
	return result;
}