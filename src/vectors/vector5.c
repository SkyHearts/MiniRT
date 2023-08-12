/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:44:51 by sulim             #+#    #+#             */
/*   Updated: 2023/08/12 13:39:02 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

t_mat44	add_mat(t_mat44 matrix_a, t_mat44 matrix_b)
{
	t_mat44	result;
	int		i;
	int		j;

	i = -1;
	while (++i <= 3)
	{
		j = -1;
		while (++j <= 3)
			result.data[i][j] = matrix_a.data[i][j] + matrix_b.data[i][j];
	}
	return (result);
}

t_mat44	worldtocam(t_mat44 ctw)
{
	t_mat44	wtc;
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;
	t_vec3	trans;

	right = vec3(ctw.data[0][0], ctw.data[1][0], ctw.data[2][0]);
	up = vec3(ctw.data[0][1], ctw.data[1][1], ctw.data[2][1]);
	forward = vec3(ctw.data[0][2], ctw.data[1][2], ctw.data[2][2]);
	trans = vec3(ctw.data[0][3], ctw.data[1][3], ctw.data[2][3]);
	wtc.data[0][0] = ctw.data[0][0];
	wtc.data[0][1] = ctw.data[1][0];
	wtc.data[0][2] = ctw.data[2][0];
	wtc.data[0][3] = -dot_vec3(right, trans);
	wtc.data[1][0] = ctw.data[0][1];
	wtc.data[1][1] = ctw.data[1][1];
	wtc.data[1][2] = ctw.data[2][1];
	wtc.data[1][3] = -dot_vec3(up, trans);
	wtc.data[2][0] = ctw.data[0][2];
	wtc.data[2][1] = ctw.data[1][2];
	wtc.data[2][2] = ctw.data[2][2];
	wtc.data[2][3] = -dot_vec3(forward, trans);
	wtc.data[3][0] = 0;
	return (wtc.data[3][1] = 0, wtc.data[3][2] = 0, wtc.data[3][3] = 1, wtc);
}

void	print_vec(t_vec3 a)
{
	printf("[%f,%f,%f]\t", a.x, a.y, a.z);
}
