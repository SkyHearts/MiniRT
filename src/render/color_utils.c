/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:05:24 by sulim             #+#    #+#             */
/*   Updated: 2023/08/15 13:57:12 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_color	clamp_vec(t_color *col, t_vec3 min, double max)
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
