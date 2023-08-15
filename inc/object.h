/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:37:39 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 12:44:24 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef struct s_hit_record
{
	double		t;
	t_object	*obj;
	t_vec3		normal;
	t_vec3		poi;
	t_vec3		cap_normal;
	int			iscap;
	t_vec3		light_direction;
	t_color		ret_color;
}	t_hit_record;

typedef struct s_sphere
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	t0;
	double	t1;
	double	discriminant;
}				t_sphere;

typedef struct s_plane
{
	double	denom;
	double	t;
	double	discriminant;
}				t_plane;

//v = ray.dir, va = cylinder dir
//cylinder pos + (cylinder height * cylinder dir)
//(v.va)
//ray dir - (raynormal * va)
//ray origin - cylinder origin
//cylinder pos + (cylinder height * cylinder dir)
typedef struct s_cylinder
{
	t_vec3	top;
	double	raynormal;
	t_vec3	cyp;
	t_vec3	delta_p;
	double	a;
	double	b;
	double	c;
	double	t0;
	double	t1;
	double	discriminant;
}	t_cylinder;

typedef struct s_cylinder2
{
	t_vec3	top;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	t0;
	double	t1;
	double	discriminant;
}				t_cylinder2;

typedef struct s_cone
{
	t_vec3	top;
	t_vec3	oc;
	double	theta;
	double	rad;
	double	a;
	double	b;
	double	c;
	double	t0;
	double	t1;
	double	discriminant;
}				t_cone;

#endif