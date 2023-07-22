/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:34:51 by jyim              #+#    #+#             */
/*   Updated: 2023/07/22 15:36:36 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minirt.h"
#include "../inc/scene.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

void	print_vec(t_vec3 a)
{
	printf("[%f,%f,%f]\t", a.x, a.y, a.z);
}

void	print_ambient(t_mlx	rt)
{
	printf("AMBIENT:\tRatio:%f\t\tcolor:", rt.scene.ambient.ratio);
	print_vec(rt.scene.ambient.color);
	printf("\n");
}

void	print_cam(t_mlx	rt)
{
	printf("Camera:\t\tposition:");
	print_vec(rt.scene.camera.position);
	printf("\torientation:");
	print_vec(rt.scene.camera.direction);
	printf("\tFOV:%f\n", rt.scene.camera.vars.fov);
}

void	print_light(t_mlx	rt)
{
	if (rt.scene.light)
	{
		int i = 0;
		t_light *light = rt.scene.light;
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
	if (rt.scene.object)
	{
		t_object *obj = rt.scene.object;
		while (obj != NULL)
		{
			printf("Object %d:\tType:", obj->index);
			if (obj->type == 0)
			{
				printf("SPHERE:\tPosition:");
				print_vec(obj->position);
				printf("\tDiameter:%f",obj->diameter);
				printf("\tRGB:");
				print_vec(obj->color);
				printf("\n");
			}
			else if (obj->type == 1)
			{
				printf("PLANE:\tPosition:");
				print_vec(obj->position);
				printf("\tNormal:");
				print_vec(obj->normal);
				printf("\tRGB:");
				print_vec(obj->color);
				printf("\n");
			}
			else if (obj->type == 2)
			{
				printf("CYLINDER:\tPosition:");
				print_vec(obj->position);
				printf("\tNormal:");
				print_vec(obj->normal);
				printf("\tDiameter:%f",obj->diameter);
				printf("\tHeight:%f",obj->height);
				printf("\tRGB:");
				print_vec(obj->color);
				printf("\n");
			}
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