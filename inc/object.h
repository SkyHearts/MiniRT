/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:37:39 by jyim              #+#    #+#             */
/*   Updated: 2023/08/08 13:09:17 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef struct s_hit_record
{
	double	t;
	t_vec3	obj_normal;
	t_vec3	point_of_interaction;
	t_vec3	light_direction;
	t_light	*current_light;
	double	intensity;
	int		validIllum;
	color	illum_color;

	t_object *obj;
}	t_hit_record;

typedef struct s_sphere
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}				t_sphere;
#endif