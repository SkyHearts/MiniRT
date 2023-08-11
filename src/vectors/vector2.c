/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:34:28 by sulim             #+#    #+#             */
/*   Updated: 2023/08/11 10:37:39 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

void	printvec_nl(t_vec3 vec)
{
	printf("[%f, %f, %f]\n", vec.x, vec.y, vec.z);
}

t_vec3	mul_double_vec3(double num, t_vec3 vec)
{
	t_vec3	result;

	result.x = vec.x * num;
	result.y = vec.y * num;
	result.z = vec.z * num;
	return (result);
}

t_vec3	div_double_vec3(double num, t_vec3 vec)
{
	t_vec3	result;

	result.x = vec.x / num;
	result.y = vec.y / num;
	result.z = vec.z / num;
	return (result);
}

double	dot_vec3(t_vec3 vec1, t_vec3 vec2)
{
	double	result;

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
