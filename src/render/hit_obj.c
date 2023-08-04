/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/04 21:27:18 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

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
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;
	return (rec->t);
} 

// printvec_nl(rec.obj->color);