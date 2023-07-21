/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:59:11 by jyim              #+#    #+#             */
/*   Updated: 2023/07/18 17:59:11 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minirt.h"
#include "../inc/scene.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

void	init_mlx(t_mlx *rt)
{
	rt->element = ft_split("A C L sp pl cy", ' ');
	rt->win_height = 720;
	rt->win_width = 1080;
	rt->scene.camera.filled = 0;
	rt->scene.active_camera = NULL;
	rt->scene.light = NULL;
	rt->scene.object = NULL;
	rt->scene.active_object = NULL;
	rt->scene.ambient.filled = 0;
}
void	print_vec(t_vec3 a)
{
	printf("[%f,%f,%f]\t", a.x, a.y, a.z);
}

void	print_ambient(t_mlx	rt)
{
	printf("AMBIENT:\tRatio:%f\tcolor:", rt.scene.ambient.ratio);
	print_vec(rt.scene.ambient.color);
	printf("\n");
}

void	print_cam(t_mlx	rt)
{
	printf("Camera:\tposition:");
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
			printf("Camera %d:\tposition:", ++i);
			print_vec(rt.scene.camera.position);
			printf("\torientation:");
			print_vec(rt.scene.camera.direction);
			printf("\tFOV:%f\n", rt.scene.camera.vars.fov);
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
			printf("Object %d:\ttype:", obj->index);
			if (obj->type == 0)
			{
				printf("SPHERE:\tposition:");
				print_vec(obj->position);
				printf("\tdiameter:%f",obj->diameter);
				printf("\tRGB:");
				print_vec(obj->color);
				printf("\n:");
			}
			else if (obj->type == 2)
			{
				printf("PLANE:\tposition:");
				print_vec(obj->position);
				printf("\tnormal:");
				print_vec(obj->normal);
				printf("\tRGB:");
				print_vec(obj->color);
				printf("\n:");
			}
			else if (obj->type == 3)
			{
				printf("CYLINDER:\tposition:");
				print_vec(obj->position);
				printf("\tnormal:");
				print_vec(obj->normal);
				printf("\tdiameter:%f",obj->diameter);
				printf("\theight:%f",obj->height);
				printf("\tRGB:");
				print_vec(obj->color);
				printf("\n:");
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

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_mlx rt;
		int ret;
		init_mlx(&rt);
		ret = parse_scene(argv[1], &rt);
		if (ret == 1)
			ft_printf("ERROR!\n");
		ft_printscene(rt);
		// if (parse_scene(argv[1], &rt))
		//		//free scene
		//		//parse error exit(1)


	}
	else
		printf("Wrong number of argument/format! ./minirt <filename>");
}
