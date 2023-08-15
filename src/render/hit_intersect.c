/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:28:01 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 13:49:28 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

double	hit_sphere(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_sphere	sphere;

	sphere.oc = sub_vec3(r.origin, obj->position);
	sphere.a = dot_vec3(r.direction, r.direction);
	sphere.b = 2.0 * dot_vec3(sphere.oc, r.direction);
	sphere.c = dot_vec3(sphere.oc, sphere.oc) - (obj->radius * obj->radius);
	sphere.discriminant = sphere.b * sphere.b - 4 * sphere.a * sphere.c;
	if (sphere.discriminant < 0)
		return (FALSE);
	else
	{
		sphere.t0 = (-sphere.b - sqrt(sphere.discriminant)) / (2.0 * sphere.a);
		sphere.t1 = (-sphere.b + sqrt(sphere.discriminant)) / (2.0 * sphere.a);
		if (sphere.t0 < 0 && sphere.t1 < 0)
			return (FALSE);
		else if (sphere.t0 < 0.0)
			sphere.t0 = sphere.t1;
		else if (sphere.t1 < 0.0)
			sphere.t1 = sphere.t0;
		obj->t = fmin(sphere.t1, sphere.t0);
	}
	update_rec(obj, r, rec, record);
	return (TRUE);
}

double	hit_plane(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	double	denom;
	double	ret;
	t_vec3	normal;

	normal = obj->normal;
	denom = dot_vec3(r.direction, normal);
	if (fabs(denom) < 1e-6)
		return (FALSE);
	ret = dot_vec3(sub_vec3(obj->position, r.origin), obj->normal) / denom;
	if (ret < 1e-6)
		return (FALSE);
	else
		obj->t = ret;
	update_rec(obj, r, rec, record);
	return (TRUE);
}

//(q - pa - (va.q - pa)va)^2 - r^2 = 0
//where q is any point on cylinder, r.o + t * r.dir, point
//pa is position of cylinder in world, point
//va is normalized orientation of cylinder, vector
//(r.o + t * r.dir - pa - (va . (r.o + t * r.dir) - pa)va)^2 - r^2 = 0
//oc is point of ray.origin to coordinate of obj, delta.p
///* in circular range condition */
//t_vec3	plane;
//plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t,
//				r.direction)), top);
//if (dot_vec3(plane, plane) > (obj->radius * obj->radius))
//	return (FALSE);
double	top_cap2(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_vec3	top;
	double	denom;
	double	ret;

	top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	denom = dot_vec3(r.direction, obj->normal);
	if (fabs(denom) < 1e-6)
		return (FALSE);
	ret = dot_vec3(sub_vec3(top, r.origin), obj->normal) / denom;
	if (ret < 1e-6)
		return (FALSE);
	else
		obj->t = ret;
	if (length(sub_vec3(get_intersect(r, obj->t), top)) > obj->radius)
		return (FALSE);
	update_rec2(obj, r, rec, record);
	return (TRUE);
}

///* in circular range condition */
//t_vec3	plane;
//plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t,
//				r.direction)), obj->position);
//if (dot_vec3(plane, plane) > (obj->radius * obj->radius))
//	return (FALSE);
double	btm_cap2(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	double	denom;
	double	ret;

	denom = dot_vec3(r.direction, obj->normal);
	if (fabs(denom) < 1e-6)
		return (FALSE);
	ret = dot_vec3(sub_vec3(obj->position, r.origin), obj->normal) / denom;
	if (ret < 1e-6)
		return (FALSE);
	else
		obj->t = ret;
	if (length(sub_vec3(get_intersect(r, obj->t), obj->position)) > obj->radius)
		return (FALSE);
	update_rec3(obj, r, rec, record);
	return (TRUE);
}

double	hit_cylinder(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_cylinder2	cy;

	top_cap2(obj, r, rec, record);
	btm_cap2(obj, r, rec, record);
	assign_cylinder(&cy, obj, r);
	if (cy.discriminant < 0)
		return (FALSE);
	else
	{
		cy.t0 = (-cy.b - sqrt(cy.discriminant)) / (2.0 * cy.a);
		cy.t1 = (-cy.b + sqrt(cy.discriminant)) / (2.0 * cy.a);
		if (cy.t0 < EPS && cy.t1 < EPS)
			return (FALSE);
		else if (cy.t0 < 0.0)
			cy.t0 = cy.t1;
		else if (cy.t1 < 0.0)
			cy.t1 = cy.t0;
		obj->t = fmin(cy.t1, cy.t0);
	}
	if (dot_vec3(obj->normal, sub_vec3(get_intersect(r, obj->t), cy.top)) > 0)
		return (top_cap2(obj, r, rec, 0));
	if (dot_vec3(obj->normal, sub_vec3(get_intersect(r, obj->t),
				obj->position)) < 0)
		return (btm_cap2(obj, r, rec, 0));
	return (update_rec(obj, r, rec, record), TRUE);
}
	///* retained for debug purposes */
	//if (dot_vec3(obj->normal, add_vec3(r.origin,
	//		mul_double_vec3(obj->t, r.direction))) > obj->height)
	//	return (FALSE);
	//	return (top_cap2(obj, r, rec, record));
	//if (dot_vec3(obj->normal, add_vec3(r.origin,
	//		mul_double_vec3(obj->t, r.direction))) > 0)
	//	return (FALSE);
	//	return (btm_cap2(obj, r, rec, record));
	//if (top_cap2(obj, r, rec, record))
	//	return (TRUE);
	//if (btm_cap2(obj, r, rec, record))
	//	return (TRUE);
