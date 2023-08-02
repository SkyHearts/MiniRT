/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/02 14:21:35 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

int	hit_object(t_ray r, t_object *obj)
{
	int			hit;
	// t_object	*current_obj;
	hit = 0;
	// current_obj = obj;
	
	// while (current_obj != NULL)
	// {
		if (obj->type == 0)
			hit = hit_sphere(obj, r);
		if (obj->type == 1)
			hit = hit_plane(obj, r);
		// else if (current_obj->type == 1)
		// 	hit = hit_plane(current_obj, r);
		// else if (current_obj->type == 2)
		// 	hit = hit_cylinder(current_obj, r);
	// 	current_obj = current_obj->next;
	// }
	return (hit);
} 
