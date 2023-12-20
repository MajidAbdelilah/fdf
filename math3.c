/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:45:25 by amajid            #+#    #+#             */
/*   Updated: 2023/12/20 19:46:12 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// [a b c d][A B C D]   [aA+bE+cI+dM
// [e f g h][E F G H] = [eA+fE+gI+hM ...
// [i j k l][I J K L]
// [m n o p][M N O P]

t_matrix4f	matrix4x4_mul(t_matrix4f left, t_matrix4f right)
{
	t_matrix4f	result;
	int			i;
	int			j;

	i = 0;
	result = get_identity_matrix();
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = left.m[0][j] * right.m[i][0] + left.m[1][j]
				* right.m[i][1] + left.m[2][j] * right.m[i][2]
				+ left.m[3][j] * right.m[i][3];
			j++;
		}
		i++;
	}
	return (result);
}
