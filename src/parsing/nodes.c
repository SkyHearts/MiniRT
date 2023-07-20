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

t_vec3 get_coordinate(char *pos)
{
	t_vec3 coor;
	char **pos;

	pos = ft_split(pos, ',');
	coor.x = ft_atof(pos[0]);
	coor.y = ft_atof(pos[1]);
	coor.z = ft_atof(pos[2]);
	return (free_darray(pos), coor);
	
}

t_vec3 get_color(char *color)
{
	t_vec3 color;
	char **c;

	color = ft_split(split[3], ',');
	(*obj)->color.x = ft_atof(color[0]);
	(*obj)->color.y =  ft_atof(color[1]);
	(*obj)->color.z =  ft_atof(color[2]);
}

t_vec3 get_normal(char *color)
{
	color = ft_split(split[3], ',');
	(*obj)->color.x = ft_atof(color[0]);
	(*obj)->color.y =  ft_atof(color[1]);
	(*obj)->color.z =  ft_atof(color[2]);
}

void	add_sphere(char **split, t_object **obj)
{
	char **pos;
	char **color;
	(*obj)->type = SPHERE;
	(*obj)->position = get_coordinate(split[1]);

	color = ft_split(split[3], ',');
	(*obj)->color.x = ft_atof(color[0]);
	(*obj)->color.y =  ft_atof(color[1]);
	(*obj)->color.z =  ft_atof(color[2]);
	free_darray(pos);
	free_darray(color);
}

void	add_plane(char **split, t_object **obj)
{
	char **pos;
	char **color;
	(*obj)->type = PLANE;
	(*obj)->index = 1;
	pos = ft_split(split[1], ',');
	(*obj)->position.x = ft_atof(pos[0]);
	(*obj)->position.y = ft_atof(pos[1]);
	(*obj)->position.z = ft_atof(pos[2]);
	(*obj)->normal.x =  ft_atof(split[2]);
	color = ft_split(split[3], ',');
	(*obj)->color.x = ft_atof(color[0]);
	(*obj)->color.y =  ft_atof(color[1]);
	(*obj)->color.z =  ft_atof(color[2]);
	free_darray(pos);
	free_darray(color);
}

void	add_cylinder(char **split, t_object **obj)
{

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

void	ft_objadd_back(t_light **lst, t_light *new)
{
	t_object	*tmp;
	int			i;

	i = 0;
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
	char **pos;
	char **color;

	head = malloc(sizeof(t_light));
	if (!head)
		return (0);
	pos = ft_split(split[1], ',');
	head->position.x = ft_atof(pos[0]);
	head->position.y = ft_atof(pos[1]);
	head->position.z = ft_atof(pos[2]);
	head->ratio =  ft_atof(split[2]);
	color = ft_split(split[3], ',');
	head->color.x = ft_atof(color[0]);
	head->color.y =  ft_atof(color[1]);
	head->color.z =  ft_atof(color[2]);
	head->next = NULL;
	return (free_darray(pos), free_darray(color), head);
}

void	ft_lightadd_back(t_light **lst, t_light *new)
{
	t_light	*tmp;

	tmp = (*lst);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}