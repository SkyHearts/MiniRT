/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukilim <sukilim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/07/30 16:35:14 by sukilim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

t_range	set_range(const float min, const float max)
{
	t_range	x;

	x.t_min = min;
	x.t_max = max;
	return (x);
}

static float	adj(t_hit_record *tmp, t_hit_record *rec, t_color3 *color)
{
	tmp->c = *color;
	*rec = *tmp;
	return (tmp->t);
}

int	hit_objects(t_ray *r, t_object *obj,
					t_hit_record *rec, t_range rng)
{
	t_utils			u;

	u.hit = 0;
	u.it = obj;
	while (obj->type == 0)
	{
		if (hit_sphere(r, u.it, &u.rec, rng))
		{
			u.hit = 1;
			rng.t_max = adj(&u.rec, rec, &((t_object *) u.it)->color);
		}
		u.it = ((t_object *) u.it)->next;
	}

	while (obj->type == 1)
	{
		if (hit_plane(r, u.it, &u.rec, rng))
		{
			u.hit = 1;
			rng.t_max = adj(&u.rec, rec, &((t_object *) u.it)->color);
		}
		u.it = ((t_object *) u.it)->next;
	}

	while (obj->type == 2)
	{
		if (hit_cylinder(r, u.it, &u.rec, rng))
		{
			u.hit = 1;
			rng.t_max = adj(&u.rec, rec, &((t_object *) u.it)->color);
		}
		u.it = ((t_object *) u.it)->next;
	}
	return (u.hit);
} 
