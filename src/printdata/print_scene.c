/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:34:51 by jyim              #+#    #+#             */
/*   Updated: 2023/08/12 16:33:50 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <stdio.h>

//print Ambient light data
void	print_ambient(t_mlx	rt)
{
	printf("AMBIENT:\tRatio:%f\t\tcolor:", rt.scene.ambient.ratio);
	print_vec(rt.scene.ambient.color);
	printf("\n");
}

//print camera data
void	print_cam(t_mlx	rt)
{
	printf("Camera:\t\tposition:");
	print_vec(rt.scene.camera.position);
	printf("\torientation:");
	print_vec(rt.scene.camera.direction);
	printf("\tFOV:%f\n", rt.scene.camera.vars.fov);
}

//print Lights data
void	print_light(t_mlx	rt)
{
	int		i;
	t_light	*light;

	i = 0;
	light = rt.scene.light;
	if (rt.scene.light)
	{
		while (light != NULL)
		{
			printf("Light %d:\tposition:", ++i);
			print_vec(light->position);
			printf("\tBrightness:%f", light->ratio);
			printf("\tRGB:");
			print_vec(light->color);
			printf("\n");
			light = light->next;
		}
	}
}

//SPHERE = 0,
//PLANE = 1,
//CYLINDER = 2,
void	print_obj(t_mlx	rt)
{
	t_object	*obj;

	obj = rt.scene.object;
	if (rt.scene.object)
	{
		while (obj != NULL)
		{
			printf("Object %d:\tType:", obj->index);
			if (obj->type == 0)
				print_sphere(obj);
			else if (obj->type == 1)
				print_plane(obj);
			else if (obj->type == 2)
				print_cylinder(obj);
			else if (obj->type == 3)
				print_cone(obj);
			obj = obj->next;
		}
	}
}

void	ft_printscene(t_mlx	rt)
{
	print_ambient(rt);
	print_cam(rt);
	print_light(rt);
	print_obj(rt);
}
