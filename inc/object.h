/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukilim <sukilim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:37:39 by jyim              #+#    #+#             */
/*   Updated: 2023/07/30 15:09:12 by sukilim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef struct s_utils
{
	t_hit_record	rec;
	bool			hit;
	void			*it;
	float			l_dist;
}	t_utils;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		n;
	t_color3	c;
	float		t;
}	t_hit_record;

typedef struct s_range
{
	float	t_min;
	float	t_max;
}	t_range;

typedef struct s_sphere
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}				t_sphere;
#endif