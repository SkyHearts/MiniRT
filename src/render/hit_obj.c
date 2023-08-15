/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 13:48:14 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

t_vec3	get_intersect(t_ray r, double t)
{
	t_vec3	poi;

	poi = add_vec3(r.origin, mul_double_vec3(t, r.direction));
	return (poi);
}

t_vec3	get_cy_normal(t_ray r, t_object *obj, t_hit_record *rec, t_vec3 poi)
{
	double	height;
	t_vec3	normal;

	(void)rec;
	height = dot_vec3(normalize(obj->normal), sub_vec3(poi, obj->position));
	normal = normalize(sub_vec3(poi, add_vec3(obj->position,
					mul_double_vec3(height, obj->normal))));
	if (dot_vec3(r.direction, rec->cap_normal) > 0.0 && rec->iscap)
		normal = mul_double_vec3(-1, rec->cap_normal);
	else if (rec->iscap)
		normal = rec->cap_normal;
	else if (dot_vec3(r.direction, normal) > 0.0)
		normal = mul_double_vec3(-1, normal);
	return (normal);
}

t_vec3	get_obj_normal2(t_ray r, t_object *obj, t_hit_record *rec, t_vec3 poi)
{
	t_vec3	normal;
	double	height;

	height = 0;
	normal = vec3(0, 0, 0);
	if (obj->type == 0)
	{
		normal = normalize(sub_vec3(poi, obj->position));
		if (dot_vec3(r.direction, normal) > 0.0)
			normal = mul_double_vec3(-1, normal);
	}
	else if (obj->type == 1)
		normal = obj->normal;
	if (obj->type == 2)
		normal = get_cy_normal(r, obj, rec, poi);
	if (obj->type == 3)
		normal = get_cone_normal(r, obj, rec, poi);
	return (normal);
}

// Iterate through objects and return a updated
// record of closest hit object and properties
int	hit_object(t_ray r, t_object *obj, t_hit_record *rec, int record)
{
	int			hit;
	t_object	*current_obj;
	int			hitted;

	hit = 0;
	current_obj = obj;
	rec->t = INFINITY;
	hitted = 0;
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r, rec, record);
		else if (current_obj->type == 1)
			hit = hit_plane(current_obj, r, rec, record);
		else if (current_obj->type == 2)
			hit = hit_cylinder(current_obj, r, rec, record);
		else if (current_obj->type == 3)
			hit = hit_cone(current_obj, r, rec, record);
		if (hit)
			hitted = 1;
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		hitted = 0;
	return (hitted);
}
