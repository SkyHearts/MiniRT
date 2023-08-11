/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:41:06 by sulim             #+#    #+#             */
/*   Updated: 2023/08/11 10:44:36 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

void	print_matrix(t_mat44 matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		printf("[");
		j = 0;
		while (j < 4)
		{
			printf("%15f ", matrix.data[i][j]);
			j++;
		}
		printf("]\n");
		i++;
	}
}

void	set_zero(t_mat44 *matrix)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix->data[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void	set_identity(t_mat44 *matrix)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				matrix->data[i][j] = 1.0;
			else
				matrix->data[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void	get_translation(t_vec3 position, t_mat44 *translation)
{
	set_zero(translation);
	translation->data[0][3] = position.x;
	translation->data[1][3] = position.y;
	translation->data[2][3] = position.z;
}

void	get_rotation(t_camera *camray, t_mat44 *rotation)
{
	set_identity(rotation);
	rotation->data[0][0] = camray->vars.right.x;
	rotation->data[0][1] = camray->vars.right.y;
	rotation->data[0][2] = camray->vars.right.z;
	rotation->data[1][0] = camray->vars.up.x;
	rotation->data[1][1] = camray->vars.up.y;
	rotation->data[1][2] = camray->vars.up.z;
	rotation->data[2][0] = camray->vars.forward.x;
	rotation->data[2][1] = camray->vars.forward.y;
	rotation->data[2][2] = camray->vars.forward.z;
}
