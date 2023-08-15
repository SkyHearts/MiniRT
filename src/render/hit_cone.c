/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:00:42 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 14:03:26 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

t_vec3	get_cone_normal(t_ray r, t_object *obj, t_hit_record *rec, t_vec3 poi)
{
	double	height;
	t_vec3	normal;
	t_vec3	tan1;
	t_vec3	tan2;

	(void)rec;
	height = dot_vec3(normalize(obj->normal), sub_vec3(poi, obj->position));
	tan1 = sub_vec3(poi, obj->position);
	tan2 = cross_vec3(tan1, sub_vec3(poi, add_vec3(obj->position,
					mul_double_vec3(height, obj->normal))));
	normal = normalize(cross_vec3(tan1, tan2));
	if (dot_vec3(r.direction, rec->cap_normal) > 0.0 && rec->iscap)
			normal = mul_double_vec3(-1, rec->cap_normal);
	else if (rec->iscap)
			normal = rec->cap_normal;
	else if (dot_vec3(r.direction, normal) > 0.0)
		normal = mul_double_vec3(-1, normal);
	return (normal);
}

double	cone_cap(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_vec3	top;
	double	denom;
	double	ret;
	double	radius;

	top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	denom = dot_vec3(r.direction, obj->normal);
	if (fabs(denom) < 1e-6)
		return (FALSE);
	ret = dot_vec3(sub_vec3(top, r.origin), obj->normal) / denom;
	if (ret < 1e-6)
		return (FALSE);
	else
		obj->t = ret;
	radius = obj->height * tan(obj->rad);
	if (length(sub_vec3(get_intersect(r, obj->t), top)) > radius)
		return (FALSE);
	update_rec2(obj, r, rec, record);
	return (TRUE);
}

void	assign_cone(t_cone *cn, t_object *obj, t_ray r)
{
	cn->top = add_vec3(obj->position,
			mul_double_vec3(obj->height, obj->normal));
	cn->oc = sub_vec3(r.origin, obj->position);
	cn->a = (dot_vec3(r.direction, obj->normal) \
			* dot_vec3(r.direction, obj->normal)) \
			- (cos(obj->rad) * cos(obj->rad));
	cn->b = 2.0 * ((dot_vec3(r.direction, obj->normal) \
			* dot_vec3(cn->oc, obj->normal)) - (dot_vec3(r.direction, cn->oc) \
			* (cos(obj->rad) * cos(obj->rad))));
	cn->c = (dot_vec3(cn->oc, obj->normal) * dot_vec3(cn->oc, obj->normal)) \
			- (dot_vec3(cn->oc, cn->oc) * (cos(obj->rad) * cos(obj->rad)));
	cn->discriminant = cn->b * cn->b - 4 * cn->a * cn->c;
	cn->t0 = (-cn->b - sqrt(cn->discriminant)) / (2.0 * cn->a);
	cn->t1 = (-cn->b + sqrt(cn->discriminant)) / (2.0 * cn->a);
}

double	apex(t_object *obj, t_ray r, t_hit_record *rec, t_cone *cn)
{
	double	h0;
	double	h1;

	h0 = dot_vec3(normalize(obj->normal), \
		sub_vec3(get_intersect(r, cn->t0), obj->position));
	h1 = dot_vec3(normalize(obj->normal), \
		sub_vec3(get_intersect(r, cn->t1), obj->position));
	if (h1 < EPS)
		return (FALSE);
	if (h0 < EPS && h1 > EPS)
		obj->t = cn->t1;
	if (h1 > obj->height)
		return (FALSE);
	if (rec->t > obj->t)
	{
		rec->iscap = 0;
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->cap_normal = mul_double_vec3(1, obj->normal);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
	return (TRUE);
}

double	hit_cone(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_cone	cn;
	double	h;
	t_vec3	poi;

	cone_cap(obj, r, rec, record);
	assign_cone(&cn, obj, r);
	if (cn.discriminant < 0)
		return (FALSE);
	else
	{
		if (cn.t0 < EPS && cn.t1 < EPS)
			return (FALSE);
		if (cn.t0 < 0.0)
			cn.t0 = cn.t1;
		else if (cn.t1 < 0.0)
			cn.t1 = cn.t0;
		obj->t = fmin(cn.t1, cn.t0);
	}
	poi = get_intersect(r, obj->t);
	h = dot_vec3(normalize(obj->normal), sub_vec3(poi, obj->position));
	if (h < EPS)
		return (apex(obj, r, rec, &cn));
	if (h >= obj->height)
		return (cone_cap(obj, r, rec, record));
	return (update_rec(obj, r, rec, record), TRUE);
}
