/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:28:55 by jyim              #+#    #+#             */
/*   Updated: 2023/07/24 13:19:34 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR3_H
# define VECTOR3_H

# include <math.h>
# include <stdlib.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_mat44
{
	double data[4][4];
}				t_mat44;

t_vec3	*create_vec3(double _x, double _y, double _z);
t_vec3	vec3(double _x, double _y, double _z);
t_vec3	add_vec3(t_vec3 vector1, t_vec3 vector2);
t_vec3	sub_vec3(t_vec3 vec1, t_vec3 vec2);
double	dot_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3	cross_vec3(t_vec3 vec1, t_vec3 vec2);
t_vec3	*pnormalize(t_vec3 vec);
t_vec3	normalize(t_vec3 vec);

//matrix
void	set_identity(t_mat44 *matrix);
void	get_translation(t_vec3 position, t_mat44 *translation);
void	get_rotation(t_camera camray, t_mat44 rotation);

#endif