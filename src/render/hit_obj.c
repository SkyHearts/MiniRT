/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/04 21:24:32 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

int ft_shadow()
{
		// Shadow, so no illumination.
		color = m_color;
		intensity = 0.0;
		return 0;
}

int ft_illuminate()
{
	// Compute the angle between the local normal and the light ray.
	// Note that we assume that localNormal is a unit vector.
	double angle = acos(qbVector<double>::dot(localNormal, lightDir));
	
	// If the normal is pointing away from the light, then we have no illumination.
	if (angle > 1.5708)
	{
		// No illumination.
		color = m_color;
		intensity = 0.0;
		return 0;
	}
	else
	{
		// We do have illumination.
		color = m_color;
		intensity = m_intensity * (1.0 - (angle / 1.5708));
		return 1;
	}

}

int	hit_object(t_ray r, t_object *obj, t_hit_record *rec)
{
	int			hit;
	t_object	*current_obj;
	hit = 0;
	current_obj = obj;

	//(void) rec;
	
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r);
		if (current_obj->type == 1)
			hit = hit_plane(current_obj, r);
		// else if (current_obj->type == 2)
		// 	hit = hit_cylinder(current_obj, r);
		
		if (rec->t > current_obj->t && current_obj->t != -1)
		{
			rec->t = current_obj->t;
			rec->obj = current_obj;
		}
		if (hit)
			ft_shadow();
		else
			ft_illuminate();
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;
	return (rec->t);
} 

// printvec_nl(rec.obj->color);