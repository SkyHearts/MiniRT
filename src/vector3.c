/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:17:04 by jyim              #+#    #+#             */
/*   Updated: 2023/07/05 10:37:51 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	*create_vec3(float _x, float _y, float _z)
{
	t_vec3	*new_vec3;

	new_vec3 = malloc (sizeof(t_vec3) * 1);
	new_vec3->x = _x;
	new_vec3->y = _y;
	new_vec3->y = _y;
	return (new_vec3);
}

t_vec3	add_vec3(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec3	sub_vec3(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

float	dot_vec3(t_vec3 vec1, t_vec3 vec2)
{
	float	result;

	result = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (result);
}

t_vec3	cross_vec3(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (result);
}

t_vec3	*pnormalize(t_vec3 vec)
{
	t_vec3	*ret;
	float	w;

	ret = malloc (sizeof(t_vec3));
	if (!ret)
		return (NULL);
	w = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	ret->x = vec.x / w;
	ret->y = vec.y / w;
	ret->z = vec.z / w;
	return (ret);
}