/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:28:55 by jyim              #+#    #+#             */
/*   Updated: 2023/08/14 12:18:09 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include <math.h>
# include <stdlib.h>
# include <vector3.h>

//#define M_PI		3.14159265358979323846
//#define M_PI_2		1.57079632679489661923

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_mat44
{
	double	data[4][4];
}				t_mat44;

t_vec3	*create_vec3(double _x, double _y, double _z);
t_vec3	vec3(double _x, double _y, double _z);
t_vec3	add_vec3(t_vec3 vector1, t_vec3 vector2);
t_vec3	sub_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3	mul_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3	div_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3	reflect(t_vec3 raydir, t_vec3 normal);
// t_vec3	sub_double_vec3(t_vec3 vec1, t_vec3 vec2);
double	lengthsqr(t_vec3 vec);
double	length(t_vec3 vec);
t_vec3	mul_double_vec3(double num, t_vec3 vec);
t_vec3	div_double_vec3(double num, t_vec3 vec);
double	dot_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3	cross_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3	*pnormalize(t_vec3 vec);
t_vec3	normalize(t_vec3 vec);
void	printvec_nl(t_vec3 vec);
void	print_vec(t_vec3 a);
#endif