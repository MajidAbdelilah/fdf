/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:15:02 by amajid            #+#    #+#             */
/*   Updated: 2023/12/20 19:43:58 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotate(t_loop_data *data, t_point p, char direction)
{
	if (p.x && direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation(5,
					(t_point){1.0f, 0.0f, 0.0f, 0.0f}), data->rotation);
	if (p.x && !direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation(-5,
					(t_point){1.0f, 0.0f, 0.0f, 0.0f}), data->rotation);
	if (p.y && direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation(5,
					(t_point){0.0f, 1.0f, 0.0f, 0.0f}), data->rotation);
	if (p.y && !direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation(-5,
					(t_point){0.0f, 1.0f, 0.0f, 0.0f}), data->rotation);
	if (p.z && direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation(5,
					(t_point){0.0f, 0.0f, 1.0f, 0.0f}), data->rotation);
	if (p.z && !direction)
		data->rotation = matrix4x4_mul(matrix4x4_set_rotation(-5,
					(t_point){0.0f, 0.0f, 1.0f, 0.0f}), data->rotation);
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
	d->rotation = matrix4x4_set_rotation(180 - 90 * (xyz == 2),
			(t_point){xyz == 0, xyz == 1, xyz == 2, 0.0f});
	if (xyz > 2)
		xyz = 0;
}
