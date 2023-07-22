/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:28:55 by jyim              #+#    #+#             */
/*   Updated: 2023/07/22 16:39:25 by jyim             ###   ########.fr       */
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

t_vec3	*create_vec3(double _x, double _y, double _z);
t_vec3	add_vec3(t_vec3 vector1, t_vec3 vector2);


#endif