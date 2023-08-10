/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:05:24 by sulim             #+#    #+#             */
/*   Updated: 2023/08/10 23:21:54 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

color	clamp_vec(color *col)
{
	if (col->color.x < 0.0)
		col->color.x = 0.0;
	else if (col->color.x > 255)
		col->color.x = 255;
	if (col->color.y < 0.0)
		col->color.y = 0.0;
	else if (col->color.y > 255)
		col->color.y = 255;
	if (col->color.z < 0.0)
		col->color.z = 0.0;
	else if (col->color.z > 255)
		col->color.z = 255;
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
