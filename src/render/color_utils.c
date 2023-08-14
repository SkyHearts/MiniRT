/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:05:24 by sulim             #+#    #+#             */
/*   Updated: 2023/08/14 10:36:50 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

color	clamp_vec(color *col, t_vec3 min, double max)
{
	if (col->color.x < min.x)
		col->color.x = min.x;
	else if (col->color.x > max)
		col->color.x = max;
	if (col->color.y < min.y)
		col->color.y = min.y;
	else if (col->color.y > max)
		col->color.y = max;
	if (col->color.z < min.z)
		col->color.z = min.z;
	else if (col->color.z > max)
		col->color.z = max;
	return (*col);
}

t_vec3	get_shadow_origin(t_hit_record *rec)
{
	t_vec3	srayorigin;

	if (rec->iscap == 1)
		srayorigin = add_vec3(rec->poi, mul_double_vec3(EPS, rec->cap_normal));
	else
		srayorigin = add_vec3(rec->poi, mul_double_vec3(EPS, rec->normal));
	return (srayorigin);
}
