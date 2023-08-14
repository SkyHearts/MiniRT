/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:22:17 by jyim              #+#    #+#             */
/*   Updated: 2023/08/12 13:41:13 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <stdio.h>

//print SPHERE obj data
void	print_sphere(t_object *obj)
{
	printf("SPHERE:\tPosition:");
	print_vec(obj->position);
	printf("\tDiameter:%f", obj->diameter);
	printf("\tRGB:");
	print_vec(obj->color);
	printf("\n");
}

//print PLANE obj data
void	print_plane(t_object *obj)
{
	printf("PLANE:\tPosition:");
	print_vec(obj->position);
	printf("\tNormal:");
	print_vec(obj->normal);
	printf("\tRGB:");
	print_vec(obj->color);
	printf("\n");
}

//print CYLINDER obj data
void	print_cylinder(t_object *obj)
{
	printf("CYLINDER:\tPosition:");
	print_vec(obj->position);
	printf("\tNormal:");
	print_vec(obj->normal);
	printf("\tDiameter:%f", obj->diameter);
	printf("\tHeight:%f", obj->height);
	printf("\tRGB:");
	print_vec(obj->color);
	printf("\n");
}
