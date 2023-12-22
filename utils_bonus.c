/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:15:02 by amajid            #+#    #+#             */
/*   Updated: 2023/12/22 22:38:01 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotate(t_loop_data *data, t_point p, char direction)
{
	if (p.x && direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation_x(5), data->rotation);
	if (p.x && !direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation_x(-5), data->rotation);
	if (p.y && direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation_y(5), data->rotation);
	if (p.y && !direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation_y(-5), data->rotation);
	if (p.z && direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation_z(5), data->rotation);
	if (p.z && !direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation_z(-5), data->rotation);
	return (0);
}

int	translate(t_loop_data *data, t_point p, char direction)
{
	if (p.x && direction)
		data->transition.x += 60.0f;
	if (p.x && !direction)
		data->transition.x -= 60.0f;
	if (p.y && direction)
		data->transition.y += 60.0f;
	if (p.y && !direction)
		data->transition.y -= 60.0f;
	if (p.z && direction)
		data->transition.z += 60.0f;
	if (p.z && !direction)
		data->transition.z -= 60.0f;
	return (0);
}

int	scale(t_loop_data *data, t_point p, char direction)
{
	if (p.x && direction)
		data->scale.x += data->scale.x / 5;
	if (p.x && !direction)
		data->scale.x -= data->scale.x / 5;
	if (p.y && direction)
		data->scale.y += data->scale.y / 5;
	if (p.y && !direction)
		data->scale.y -= data->scale.y / 5;
	if (p.z && direction)
		data->scale.z += data->scale.z / 5;
	if (p.z && !direction)
		data->scale.z -= data->scale.z / 5;
	if (data->scale.x <= 0.00000000000f || data->scale.y <= 0.00000000000f
		|| data->scale.z <= 0.00000000000f)
		data->scale = (t_point){0.00000000001f, 0.00000000001f,
			0.000000000001f, 1.0f};
	return (0);
}

void	animate(t_loop_data *data)
{
	if (data->animate)
		rotate(data, (t_point){1, 0, 1, 0}, data->anim_dir);
}

void	multiview_orthographic_projection(t_loop_data *d)
{
	static char	xyz;

	xyz++;
	if(xyz == 0)
		d->rotation = matrix4x4_set_rotation_x(90);
	if(xyz == 1)
		d->rotation = matrix4x4_set_rotation_y(90 );
	if(xyz == 2)
		d->rotation = matrix4x4_set_rotation_z( 180);
	if (xyz >= 2)
		xyz = -1;
}
