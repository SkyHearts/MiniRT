/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:26 by sulim             #+#    #+#             */
/*   Updated: 2023/08/11 13:21:57 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

t_vec3	*create_vec3(double _x, double _y, double _z)
{
	t_vec3	*new_vec3;

	new_vec3 = malloc (sizeof(t_vec3) * 1);
	new_vec3->x = _x;
	new_vec3->y = _y;
	new_vec3->z = _z;
	return (new_vec3);
}

t_vec3	vec3(double _x, double _y, double _z)
{
	t_vec3	new_vec3;	

	new_vec3.x = _x;
	new_vec3.y = _y;
	new_vec3.z = _z;
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

t_vec3	mul_vec3(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x * vec2.x;
	result.y = vec1.y * vec2.y;
	result.z = vec1.z * vec2.z;
	return (result);
}
