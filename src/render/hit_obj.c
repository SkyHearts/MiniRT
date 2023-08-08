/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/08 13:09:15 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

void init_hit_record(t_hit_record *rec, t_ray r)
{
	rec->point_of_interaction = add_vec3(r.origin, mul_double_vec3(rec->t, r.direction));
	rec->obj_normal = get_obj_normal(rec->obj, rec->point_of_interaction);
	rec->light_direction = normalize(sub_vec3(rec->current_light->position, rec->point_of_interaction));
	rec->illum_color.color = vec3(1.0, 1.0, 1.0);
	rec->intensity = 0.0;
	rec->validIllum = 0;
}

int ft_shadow()
{
		// Shadow, so no illumination.
		return 0;
}

int ft_illuminate(t_hit_record *rec)
{
	double			angle;

	// Compute the angle between the local normal and the light ray.
	// Note that we assume that localNormal is a unit vector.
	angle = acos(dot_vec3(rec->obj_normal, rec->light_direction));
	
	// If the normal is pointing away from the light, then we have no illumination.
	if (angle > 1.5708)
	{
		// No illumination.
		return (0);

	}
	else
	{
		// We do have illumination.
		rec->intensity = 1.0 * (1.0 - (angle / 1.5708));
		rec->validIllum = 1;
	}

}

int	hit_object(t_ray r, t_object *obj, t_hit_record *rec)
{
	int			hit;
	t_object	*current_obj;
	hit = 0;
	current_obj = obj;
	
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r);
		if (current_obj->type == 1)
			hit = hit_plane(current_obj, r);
		else if (current_obj->type == 2)
			hit = hit_cylinder(current_obj, r);
		
		if (rec->t > current_obj->t && current_obj->t != -1)
		{
			rec->t = current_obj->t;
			rec->obj = current_obj;
		}
		init_hit_record(&rec, r);
		if (hit)
			ft_shadow();
		else
			ft_illuminate(&rec);
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;
	return (rec->t);
} 

// printvec_nl(rec.obj->color);