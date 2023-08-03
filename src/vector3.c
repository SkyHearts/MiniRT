/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:17:04 by jyim              #+#    #+#             */
/*   Updated: 2023/08/03 14:13:27 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	printvec_nl(t_vec3 vec)
{
	printf("[%f, %f, %f]\n", vec.x, vec.y, vec.z);
}

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
	t_vec3 reflected;

	reflected =  sub_vec3(raydir, mul_double_vec3((2 * dot_vec3(raydir, normal)), normal));
	return (reflected);
}

///////////////////////////////////////////////////////////////////////////////////////////

void print_matrix(t_mat44 matrix)
{

	int i = 0;
	while (i < 4)
	{
		printf("[");
		int j = 0;
		while (j < 4)
		{
			printf("%15f ", matrix.data[i][j]);
			j++;
		}
		printf("]\n");
		i++;
	}
}

void set_zero(t_mat44 *matrix)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix->data[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void set_identity(t_mat44 *matrix)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				matrix->data[i][j] = 1.0;
			else
				matrix->data[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void	get_translation(t_vec3 position, t_mat44 *translation)
{
	set_zero(translation);
	translation->data[0][3] = position.x;
	translation->data[1][3] = position.y;
	translation->data[2][3] = position.z;
}

void	get_rotation(t_camera *camray, t_mat44 *rotation)
{
	set_identity(rotation);
	rotation->data[0][0] = camray->vars.right.x;
	rotation->data[0][1] = camray->vars.right.y;
	rotation->data[0][2] = camray->vars.right.z;
	rotation->data[1][0] = camray->vars.up.x;
	rotation->data[1][1] = camray->vars.up.y;
	rotation->data[1][2] = camray->vars.up.z;
	rotation->data[2][0] = camray->vars.forward.x;
	rotation->data[2][1] = camray->vars.forward.y;
	rotation->data[2][2] = camray->vars.forward.z;
}

t_mat44	add_mat(t_mat44 matrix_a, t_mat44 matrix_b)
{
	t_mat44 result;

	result.data[0][0] = matrix_a.data[0][0] + matrix_b.data[0][0];
	result.data[0][1] = matrix_a.data[0][1] + matrix_b.data[0][1];
	result.data[0][2] = matrix_a.data[0][2] + matrix_b.data[0][2];
	result.data[0][3] = matrix_a.data[0][3] + matrix_b.data[0][3];
	result.data[1][0] = matrix_a.data[1][0] + matrix_b.data[1][0];
	result.data[1][1] = matrix_a.data[1][1] + matrix_b.data[1][1];
	result.data[1][2] = matrix_a.data[1][2] + matrix_b.data[1][2];
	result.data[1][3] = matrix_a.data[1][3] + matrix_b.data[1][3];
	result.data[2][0] = matrix_a.data[2][0] + matrix_b.data[2][0];
	result.data[2][1] = matrix_a.data[2][1] + matrix_b.data[2][1];
	result.data[2][2] = matrix_a.data[2][2] + matrix_b.data[2][2];
	result.data[2][3] = matrix_a.data[2][3] + matrix_b.data[2][3];
	result.data[3][0] = matrix_a.data[3][0] + matrix_b.data[3][0];
	result.data[3][1] = matrix_a.data[3][1] + matrix_b.data[3][1];
	result.data[3][2] = matrix_a.data[3][2] + matrix_b.data[3][2];
	result.data[3][3] = matrix_a.data[3][3] + matrix_b.data[3][3];
	return (result);
}

t_mat44	worldtocam(t_mat44 ctw)
{
	t_mat44 wtc;
	t_vec3 right = vec3(ctw.data[0][0],ctw.data[1][0],ctw.data[2][0]);
	t_vec3 up = vec3(ctw.data[0][1],ctw.data[1][1],ctw.data[2][1]);
	t_vec3 forward = vec3(ctw.data[0][2],ctw.data[1][2],ctw.data[2][2]);
	t_vec3 trans = vec3(ctw.data[0][3],ctw.data[1][3],ctw.data[2][3]);
	wtc.data[0][0] = ctw.data[0][0];
	wtc.data[0][1] = ctw.data[1][0];
	wtc.data[0][2] = ctw.data[2][0];
	wtc.data[0][3] = -dot_vec3(right, trans);
	wtc.data[1][0] = ctw.data[0][1];
	wtc.data[1][1] = ctw.data[1][1];
	wtc.data[1][2] = ctw.data[2][1];
	wtc.data[1][3] = -dot_vec3(up, trans);
	wtc.data[2][0] = ctw.data[0][2];
	wtc.data[2][1] = ctw.data[1][2];
	wtc.data[2][2] = ctw.data[2][2];
	wtc.data[2][3] = -dot_vec3(forward, trans);
	wtc.data[3][0] = 0;
	wtc.data[3][1] = 0;
	wtc.data[3][2] = 0;
	wtc.data[3][3] = 1;
	return (wtc);
}