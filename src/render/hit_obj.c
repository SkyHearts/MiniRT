/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/03 14:19:40 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

int	hit_object(t_ray r, t_object *obj, t_hit_record *rec)
{
	t_object	*current_obj;
	t_object	*first_obj;
	current_obj = obj;
	first_obj = obj;

	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit_sphere(current_obj, r);
		else if (current_obj->type == 1)
			hit_plane(current_obj, r);
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

// 	printvec_nl(rec->obj->color);