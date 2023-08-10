/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:36:36 by jyim              #+#    #+#             */
/*   Updated: 2023/08/09 13:37:01 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include "../../inc/scene.h"
#include "../../inc/camera.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

t_vec3	get_coordinate(char *split)
{
	t_vec3	coor;
	char	**pos;

	pos = ft_split(split, ',');
	coor.x = ft_atof(pos[0]);
	coor.y = ft_atof(pos[1]);
	coor.z = ft_atof(pos[2]);
	return (free_darray(pos), coor);
}

int	check_range(double value, int type)
{
	if (type == 1)
	{
		if (value < 0.0 || value > 1.0)
			return (1);
	}
	else if (type == 2)
	{
		if (value < -1.0 || value > 1.0)
			return (1);
	}
	else if (type == 3)
	{
		if (value < 0.0 || value > 180.0)
			return (1);
	}
	else
		printf("add type\n");
	return (0);
}

int	check_col_range(t_vec3 col)
{
	if (col.x < 0 || col.x > 255)
		return (1);
	if (col.y < 0 || col.y > 255)
		return (1);
	if (col.z < 0 || col.z > 255)
		return (1);
	return (0);
}

t_vec3	get_color(char *split)
{
	t_vec3	color;
	char	**c;

	c = ft_split(split, ',');
	color.x = ft_atof(c[0]);
	color.y = ft_atof(c[1]);
	color.z = ft_atof(c[2]);
	return (free_darray(c), color);
}

t_vec3	get_normal(char *split)
{
	t_vec3	norm;
	char	**n;

	n = ft_split(split, ',');
	norm.x = ft_atof(n[0]);
	norm.y = ft_atof(n[1]);
	norm.z = ft_atof(n[2]);
	return (free_darray(n), norm);
}
