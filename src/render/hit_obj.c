/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/08 13:15:14 by jyim             ###   ########.fr       */
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

t_vec3	get_obj_normal2(t_ray r, t_object *object, t_hit_record *rec, t_vec3 poi)
{
	t_vec3 normal;
	double	height;
	(void) rec;
	
	if (object->type == 0)
	{
		normal = normalize(sub_vec3(poi, object->position));
		if (dot_vec3(r.direction, normal) > 0.0)
			normal = mul_double_vec3(-1, normal);
	}
	else if (object->type == 1)
		normal = object->normal;
	if (object->type == 2)
	{
		height = dot_vec3(normalize(object->normal), sub_vec3(poi, object->position));
		normal = normalize(sub_vec3(poi, add_vec3(object->position, mul_double_vec3(height, object->normal))));
		if (dot_vec3(r.direction, normal) > 0.0)
			normal = mul_double_vec3(-1, normal);
	}
	return (normal);
}

int	hit_object(t_ray r, t_object *obj, t_hit_record *rec)
{
	int			hit;
	t_object	*current_obj;
	hit = 0;
	current_obj = obj;
	rec->t = INFINITY;
	//(void) rec;
	
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r, rec);
		else if (current_obj->type == 1)
			hit = hit_plane(current_obj, r, rec);
		else if (current_obj->type == 2)
		 	hit = hit_cylinder2(current_obj, r, rec);
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;
	return (rec->t);
} 


// printvec_nl(rec.obj->color);