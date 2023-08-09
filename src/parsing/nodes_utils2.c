/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:45:14 by jyim              #+#    #+#             */
/*   Updated: 2023/08/09 13:47:54 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include "../../inc/scene.h"
#include "../../inc/camera.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

// print default value of 10 used, diameter must be more than 0
// printf("Object type1: %d\n", (*obj)->type);
void	add_sphere(char **split, t_object **obj)
{
	(*obj)->type = SPHERE;
	(*obj)->position = get_coordinate(split[1]);
	(*obj)->diameter = ft_atof(split[2]);
	(*obj)->radius = ft_atof(split[2]) / 2;
	(*obj)->color = get_color(split[3]);
	if ((*obj)->diameter <= 0)
		(*obj)->diameter = 10.0;
}

// (*obj)->position = mul_double_vec3(-1,(*obj)->position);
void	add_plane(char **split, t_object **obj)
{
	(*obj)->type = PLANE;
	(*obj)->position = get_coordinate(split[1]);
	(*obj)->normal = normalize(get_normal(split[2]));
	(*obj)->color = get_color(split[3]);
}

//print default value of 10 used, diameter must be more than 0
//print default value of 10 used, height must be more than 0
void	add_cylinder(char **split, t_object **obj)
{
	(*obj)->type = CYLINDER;
	(*obj)->position = get_coordinate(split[1]);
	(*obj)->normal = get_normal(split[2]);
	(*obj)->diameter = ft_atof(split[3]);
	(*obj)->radius = ft_atof(split[3]) / 2;
	(*obj)->height = ft_atof(split[4]);
	(*obj)->color = get_color(split[5]);
	if ((*obj)->diameter <= 0)
		(*obj)->diameter = 10.0;
	if ((*obj)->height <= 0)
		(*obj)->height = 10.0;
}

void	check_type_and_input(char **split, t_object **obj)
{
	if (!ft_strcmp(split[0], "sp"))
		add_sphere(split, obj);
	else if (!ft_strcmp(split[0], "pl"))
		add_plane(split, obj);
	else if (!ft_strcmp(split[0], "cy"))
		add_cylinder(split, obj);
}

// printf("Object type2: %d\n", (*obj)->type);
//(*obj)->var.up =  normalize(cross_vec3((*obj)->var.right,
//(*obj)->var.forward));
void	init_objvar(t_object **obj)
{
	if ((*obj)->type == SPHERE)
	{
		(*obj)->var.forward = vec3(0, 0, 1);
		(*obj)->var.right = normalize(cross_vec3(get_up((*obj)->var.forward),
					(*obj)->var.forward));
		(*obj)->var.up = normalize(cross_vec3((*obj)->var.right,
					vec3(0, 0, -1)));
	}
	else
	{
		(*obj)->var.forward = normalize(sub_vec3(vec3(0, 0, 0),
					(*obj)->normal));
		(*obj)->var.right = normalize(cross_vec3(get_up((*obj)->var.forward),
					(*obj)->var.forward));
		(*obj)->var.up = normalize(cross_vec3((*obj)->var.right,
					(*obj)->var.forward));
	}
}
