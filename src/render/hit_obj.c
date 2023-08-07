/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/07 17:32:32 by jyim             ###   ########.fr       */
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
	rec->t = INFINITY;
	//(void) rec;
	
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r, rec);
		else if (current_obj->type == 1)
			hit = hit_plane(current_obj, r, rec);
		else if (current_obj->type == 2)
		{
		 	hit = hit_cylinder2(current_obj, r, rec);
			//top_cap(current_obj, r);
		}
		//if (rec->t > current_obj->t && current_obj->t != -1)
		//{
		//	rec->t = current_obj->t;
		//	rec->obj = current_obj;
		//	// printf("Obj type: %d\n", rec.obj->type);
		//	// printf("Obj color:");
		//	// printvec_nl(rec.obj->color);
		//}
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;
	return (rec->t);
} 
