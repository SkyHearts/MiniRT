/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:08:57 by jyim              #+#    #+#             */
/*   Updated: 2023/08/03 14:19:03 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

double	hit_sphere(t_object *obj, t_ray r)
{
	//center = sphere centre, radius = sphere radius
	//write data for debug
	//obj->t = -1;
	t_vec3 oc = sub_vec3(r.origin, obj->position);
	double a = dot_vec3(r.direction, r.direction);
	double b = 2.0 * dot_vec3(oc, r.direction);
	double c = dot_vec3(oc, oc) - ((obj->diameter) * (obj->diameter))/4;
	double discriminant = b * b - 4 * a * c;
	//printf("Discriminant: %f\n", discriminant);
	//return (discriminant > 0);
	if (discriminant < 0)
		obj->t = -1;
	else
	{
		double ret = (-b - sqrt(discriminant) ) / (2.0 * a);
		//printf("T: %f\n", ret);
		obj->t = ret;
	}
	return obj->t;
}




double	hit_plane(t_object *obj, t_ray r)
{
	double	denom;
	double	ret;

	//obj->t = -1;
	denom = dot_vec3(r.direction, obj->normal);
	//printf("Plane denom = %f\n", denom);
	if (denom > 0.0)
		obj->t = -1;
	else
	{	
		ret = dot_vec3(sub_vec3(obj->position, r.origin), obj->normal) / denom;
		if (ret > 0)
			obj->t = ret;
	}
	//printf("Plane\n");
	//printf("ray position =");
	//printvec_nl(r.origin);
	//printf("Plane position =");
	//printvec_nl(obj->position);
	//printvec_nl(sub_vec3(obj->position, r.origin));
	//printf("Plane nume: %f\n", dot_vec3(sub_vec3(obj->position, r.origin), obj->normal));
	//printf("Plane t = %f\n",obj->t);
	return (obj->t);
}

//double	hit_cylinder(t_object *obj, t_ray r)
//{
	
//}