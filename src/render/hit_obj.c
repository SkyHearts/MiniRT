/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/08 17:35:06 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

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
	int hittable = 0;
	
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r, rec, record);
		else if (current_obj->type == 1)
			hit = hit_plane(current_obj, r, rec, record);
		else if (current_obj->type == 2)
		 	hit = hit_cylinder2(current_obj, r, rec, record);

		if (hit > 0.0)
		{
			hittable = 1;
			ft_shadow(rec);
		}
		else
			ft_illuminate(rec);
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;

	return (hittable);
} 

// printvec_nl(rec.obj->color);