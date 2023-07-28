/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:08:57 by jyim              #+#    #+#             */
/*   Updated: 2023/07/26 16:29:21 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

double hit_sphere(t_object *obj, t_ray r)
{
	//center = sphere centre, radius = sphere radius
	//write data for debug
	t_vec3 oc = sub_vec3(r.origin, obj->position);
	double a = dot_vec3(r.direction, r.direction);
	double b = 2.0 * dot_vec3(oc, r.direction);
	double c = dot_vec3(oc, oc) - ((obj->diameter) * (obj->diameter))/4;
	double discriminant = b * b - 4 * a * c;
	//printf("Discriminant: %f\n", discriminant);
	//return (discriminant > 0);
	if (discriminant < 0)
		return -1.0;
	else
	{
		double ret = (-b - sqrt(discriminant) ) / (2.0 * a);
		//printf("T: %f\n", ret);
		return (ret);
	}
}