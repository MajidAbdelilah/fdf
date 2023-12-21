/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:24:47 by amajid            #+#    #+#             */
/*   Updated: 2023/12/21 16:48:51 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include "gnl/gnl.h"
#include "fdf.h"
#include <stdlib.h>

t_point	get_point(int x, int y, int z)
{
	t_point	result;

	result.x = x * XYZ_MUL;
	result.z = y * XYZ_MUL;
	result.y = -((float)z * XYZ_MUL);
	result.w = 1.0f;
	return (result);
}

void	adjust_result_size(t_point **result, unsigned int *size)
{
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

void	fix_positions(t_point *data, unsigned int size,
	unsigned int i_i, unsigned int j_j)
{
	t_fix_position	p;

	p = (t_fix_position){0};
	while (p.i < size)
	{
		p.max = get_max(p.max, data[p.i].y);
		p.min = get_min(p.min, data[p.i].y);
		p.i++;
	}
	p.i = 0;
	p.avg = p.max + p.min;
	while (p.i < size)
	{
		data[p.i].y -= (float)(p.avg) / 2;
		data[p.i].x -= (float)(i_i * XYZ_MUL) / 2;
		data[p.i].z -= (float)(j_j * XYZ_MUL) / 2;
		p.i++;
	}
}

char	**work0(int fd, t_pars *p)
{
	char	*line;
	char	**splited_line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	splited_line = ft_split(line, ' ');
	if (!splited_line)
		return (0);
	p->i = 0;
	while (splited_line[p->i])
	{
		if (p->index >= (p->r_size - 1))
			adjust_result_size(&p->result, &p->r_size);
		p->result[p->index++] = get_point(p->i,
				p->j, ft_atoi(splited_line[p->i]));
		p->i++;
	}
	free(line);
	return (splited_line);
}

t_point	*get_split_fdf(int fd, unsigned int *size,
	unsigned int *size_i, unsigned int *size_j)
{
	t_pars	var;
	char	**splited_line;

	var = (t_pars){700000, 0, 0, 0, 0, 0};
	var.result = malloc(sizeof(t_point) * var.r_size);
	while (1)
	{
		splited_line = work0(fd, &var);
		if (!splited_line)
			break ;
		while (splited_line[var.m])
		{
			free(splited_line[var.m]);
			var.m++;
		}
		free(splited_line);
		var.j++;
	}
	fix_positions(var.result, var.index, var.i - 1, var.j - 1);
	*size_i = var.i;
	*size_j = var.j;
	(*size) = var.index;
	return (var.result);
}
