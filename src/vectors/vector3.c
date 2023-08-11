/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:17:04 by jyim              #+#    #+#             */
/*   Updated: 2023/08/11 10:46:51 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

t_vec3	*pnormalize(t_vec3 vec)
{
	t_vec3	*ret;
	double	w;

	ret = malloc (sizeof(t_vec3));
	if (!ret)
		return (NULL);
	w = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	ret->x = vec.x / w;
	ret->y = vec.y / w;
	ret->z = vec.z / w;
	return (ret);
}

t_vec3	normalize(t_vec3 vec)
{
	t_vec3	ret;
	double	w;

	w = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	ret.x = vec.x / w;
	ret.y = vec.y / w;
	ret.z = vec.z / w;
	return (ret);
}

double	lengthsqr(t_vec3 vec)
{
	double	length;

	length = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
	return (length);
}

double	length(t_vec3 vec)
{
	double	length;

	length = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return (length);
}

//w = v - 2 * (v ∙ n) * n
t_vec3	reflect(t_vec3 raydir, t_vec3 normal)
{
	t_vec3	reflected;

	reflected = sub_vec3(raydir, mul_double_vec3((2 * dot_vec3(raydir, \
	normal)), normal));
	return (reflected);
}
