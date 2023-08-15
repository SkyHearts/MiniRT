/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:56:02 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 13:15:38 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

void	update_rec(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	if (rec->t > obj->t && record)
	{
		rec->iscap = 0;
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
}

void	update_rec2(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	if (rec->t > obj->t && record)
	{
		rec->iscap = 1;
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->cap_normal = mul_double_vec3(1, obj->normal);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
}

void	update_rec3(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	if (rec->t > obj->t && record)
	{
		rec->iscap = 1;
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->cap_normal = mul_double_vec3(-1, obj->normal);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
}

void	update_rec4(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	if (rec->t > obj->t && record)
	{
		rec->iscap = 1;
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->cap_normal = mul_double_vec3(-1, obj->normal);
		rec->normal = mul_double_vec3(1, obj->normal);
		rec->obj = obj;
	}
}

void	assign_cylinder(t_cylinder2 *cy, t_object *obj, t_ray r)
{
	cy->top = add_vec3(obj->position,
			mul_double_vec3(obj->height, obj->normal));
	cy->oc = sub_vec3(r.origin, obj->position);
	cy->a = dot_vec3(r.direction, r.direction) - (dot_vec3(r.direction,
				obj->normal) * dot_vec3(r.direction, obj->normal));
	cy->b = 2.0 * (dot_vec3(r.direction, cy->oc) - (dot_vec3(r.direction,
					obj->normal) * dot_vec3(cy->oc, obj->normal)));
	cy->c = dot_vec3(cy->oc, cy->oc) - (dot_vec3(cy->oc, obj->normal)
			* dot_vec3(cy->oc, obj->normal)) - (obj->radius * obj->radius);
	cy->discriminant = cy->b * cy->b - 4 * cy->a * cy->c;
}
