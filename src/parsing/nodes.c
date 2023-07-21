/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:33:52 by jyim              #+#    #+#             */
/*   Updated: 2023/07/19 18:33:52 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include "../../inc/scene.h"
#include "../../inc/camera.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

t_vec3 get_coordinate(char *split)
{
	t_vec3 coor;
	char **pos;

	pos = ft_split(split, ',');
	coor.x = ft_atof(pos[0]);
	coor.y = ft_atof(pos[1]);
	coor.z = ft_atof(pos[2]);
	return (free_darray(pos), coor);
	
}

int	check_range(float value, int type)
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

t_vec3 get_color(char *split)
{
	t_vec3 color;
	char **c;

	c = ft_split(split, ',');
	color.x = ft_atof(c[0]);
	color.y =  ft_atof(c[1]);
	color.z =  ft_atof(c[2]);
	
	return (free_darray(c), color);
}

t_vec3 get_normal(char *split)
{
	t_vec3 norm;
	char **n;

	n = ft_split(split, ',');
	norm.x = ft_atof(n[0]);
	norm.y =  ft_atof(n[1]);
	norm.z =  ft_atof(n[2]);
	return (free_darray(n), norm);
}

void	add_sphere(char **split, t_object **obj)
{
	(*obj)->type = SPHERE;
	(*obj)->position = get_coordinate(split[1]);
	(*obj)->diameter = ft_atof(split[2]);
	(*obj)->color = get_color(split[3]);
	if ((*obj)->diameter <= 0)
	{
		//print default value of 10 used, diameter must be more than 0
		(*obj)->diameter = 10.0;
	}	
}

void	add_plane(char **split, t_object **obj)
{
	(*obj)->type = PLANE;
	(*obj)->position = get_coordinate(split[1]);
	(*obj)->normal = get_normal(split[2]);
	(*obj)->color = get_color(split[3]);
}

void	add_cylinder(char **split, t_object **obj)
{
	(*obj)->type = CYLINDER;
	(*obj)->position = get_coordinate(split[1]);
	(*obj)->normal = get_normal(split[2]);
	(*obj)->diameter = ft_atof(split[3]);
	(*obj)->height = ft_atof(split[4]);
	(*obj)->color = get_color(split[5]);
	if ((*obj)->diameter <= 0)
	{
		//print default value of 10 used, diameter must be more than 0
		(*obj)->diameter = 10.0;
	}
	if ((*obj)->height <= 0)
	{
		//print default value of 10 used, height must be more than 0
		(*obj)->height = 10.0;
	}	
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

t_object	*ft_newobj(char **split)
{
	t_object	*head;

	head = malloc(sizeof(t_object));
	if (!head)
		return (0);
	head->index = 1;
	check_type_and_input(split, &head);
	head->next = NULL;
	return (head);
}

void	ft_objadd_back(t_object **lst, t_object *new)
{
	t_object	*tmp;
	int			i;

	i = 0;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = (*lst);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tmp->next = new;
	tmp->index += i;
}

t_light	*ft_newlight(char **split)
{
	t_light	*head;

	head = malloc(sizeof(t_light));
	if (!head)
		return (0);
	head->position = get_coordinate(split[1]);
	head->ratio =  ft_atof(split[2]);
	head->color = get_color(split[3]);
	head->next = NULL;
	return (head);
}

void	ft_lightadd_back(t_light **lst, t_light *new)
{
	t_light	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = (*lst);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}