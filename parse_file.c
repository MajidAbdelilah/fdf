#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include "gnl/get_next_line.h"
#include "fdf.h"

t_quad	get_quad()
{
	
}

t_quad	*get_split_fdf(int fd)
{
	unsigned int	r_size;
	int				i;
	int				j;
	int				atoi_ret;

	r_size = 1000;
	t_quad *result = malloc(sizeof(t_quad) * r_size);
	j = 0;
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
			atoi_ret = ft_atoi(splited_line[i]);
			i++;
		}
		j++;
	}
}