/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/02 22:30:20 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

int	hit_object(t_ray r, t_object *obj)
{
	int			hit;
	t_object	*current_obj;
	hit = 0;
	current_obj = obj;
	
	
	while (current_obj != NULL)
	{
		if (obj->type == 0)
			hit = hit_sphere(obj, r);
		// else if (current_obj->type == 1)
		// 	hit = hit_plane(current_obj, r);
		// else if (current_obj->type == 2)
		// 	hit = hit_cylinder(current_obj, r);
		
		current_obj = current_obj->next;
	}
	return (hit);
} 
