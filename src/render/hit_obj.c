/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/11 14:27:10 by jyim             ###   ########.fr       */
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
	t_vec3	normal;
	double	height;

	(void)rec;
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
		//if (dot_vec3(r.direction, normal) > 0.0 && rec->iscap)
		//	normal = mul_double_vec3(1, rec->cap_normal);
		//if (dot_vec3(r.direction, normal) > 0.0)
		//	normal = mul_double_vec3(-1, normal);
	}
	return (normal);
}

void ft_shadow(t_hit_record *rec)
{
		// Shadow, so no illumination.
		rec->illum_color.color = vec3(1.0, 1.0, 1.0);
		rec->intensity = 0.0;
		rec->validIllum = 0;
}

void ft_illuminate(t_hit_record *rec)
{
	double			angle;

	// Compute the angle between the local normal and the light ray.
	// Note that we assume that localNormal is a unit vector.
	angle = acos(dot_vec3(rec->normal, rec->light_direction));
	
	// If the normal is pointing away from the light, then we have no illumination.
	if (angle > 1.5708)
	{
		// No illumination.
		rec->illum_color.color = vec3(1.0, 1.0, 1.0);
		rec->intensity = 0.0;
		rec->validIllum = 0;
	}
	else
	{
		// We do have illumination.
		rec->illum_color.color = vec3(1.0, 1.0, 1.0);
		rec->intensity = 1.0 * (1.0 - (angle / 1.5708));
		rec->validIllum = 1;
	}
}

int	hit_object(t_ray r, t_object *obj, t_hit_record *rec, int record)
{
	int			hit;
	t_object	*current_obj;

	hit = 0;
	current_obj = obj;
	rec->t = INFINITY;
	rec->iscap = 0;
	int hitted = 0;
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r, rec, record);
		else if (current_obj->type == 1)
			hit = hit_plane(current_obj, r, rec, record);
		else if (current_obj->type == 2)
			hit = hit_cylinder(current_obj, r, rec, record);
		//if (current_obj->type == 2)
		//	hit = top_cap2(current_obj, r, rec, record);
		//if (current_obj->type == 2)
		//	hit = btm_cap2(current_obj, r, rec, record);
		if (hit)
		{
			hitted = 1;
			//ft_shadow(rec);
		}
		//else
		//	ft_illuminate(rec);
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;
	return (hitted);
}


// printvec_nl(rec.obj->color);
// printvec_nl(rec.obj->color);