/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:08:57 by jyim              #+#    #+#             */
/*   Updated: 2023/08/04 16:01:40 by jyim             ###   ########.fr       */
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
		obj->t =  -1.0;
		//return 0;
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
		//return(-1);
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


//(q - pa - (va.q - pa)va)^2 - r^2 = 0
//where q is any point on cylinder, r.o + t * r.dir, point
//pa is position of cylinder in world, point
//va is normalized orientation of cylinder, vector
//(r.o + t * r.dir - pa - (va . (r.o + t * r.dir) - pa)va)^2 - r^2 = 0
//oc is point of ray.origin to coordinate of obj, delta.p
double	hit_cylinder(t_object *obj, t_ray r)
{
	//t_vec3 oc = sub_vec3(r.origin, obj->position); //delta.p
	double	dot_raynormal = dot_vec3(r.direction, obj->normal);	//dot(ray.dir, 	obj.normal)
	t_vec3 cy = sub_vec3(r.direction, mul_double_vec3(dot_raynormal, obj->normal));
	t_vec3 delta_p = sub_vec3(r.origin, obj->position);
	t_vec3 cy_normal = sub_vec3(delta_p, mul_double_vec3(dot_vec3(delta_p, obj->normal), obj->normal));
	double a = dot_vec3(cy, cy);
	double b = 2.0 * dot_vec3(cy, cy_normal);
	double c = dot_vec3(cy_normal, cy_normal) - ((obj->diameter) * (obj->diameter)) / 4;
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		obj->t =  -1.0;
		//return 0;
	else
	{
		double ret = (-b - sqrt(discriminant) ) / (2.0 * a);
		//printf("T: %f\n", ret);
		obj->t = ret;
		//rec->normal = normalize(cy_normal);
	}
	return obj->t;
}