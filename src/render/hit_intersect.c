/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:08:57 by jyim              #+#    #+#             */
/*   Updated: 2023/08/08 17:54:58 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

t_vec3	get_intersect(t_ray r, double t)
{
	t_vec3	poi;

	poi = add_vec3(r.origin, mul_double_vec3(t, r.direction));
	return (poi);
}

t_vec3	get_obj_normal2(t_ray r, t_object *object, t_hit_record *rec, t_vec3 poi)
{
	t_vec3 normal;
	double	height;
	(void) rec;
	
	if (object->type == 0)
	{
		normal = normalize(sub_vec3(poi, object->position));
		if (dot_vec3(r.direction, normal) > 0.0)
			normal = mul_double_vec3(-1, normal);
	}
	else if (object->type == 1)
		normal = object->normal;
	if (object->type == 2)
	{
		height = dot_vec3(normalize(object->normal), sub_vec3(poi, object->position));
		normal = normalize(sub_vec3(poi, add_vec3(object->position, mul_double_vec3(height, object->normal))));
		if (dot_vec3(r.direction, normal) > 0.0)
			normal = mul_double_vec3(-1, normal);
	}
	return (normal);
}

double	hit_sphere(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_sphere sphere;
	//center = sphere centre, radius = sphere radius
	//write data for debug
	//obj->t = -1;
	//t_vec3 oc = sub_vec3(r.origin, obj->position);
	sphere.oc = sub_vec3(r.origin, obj->position);
	//double a = dot_vec3(r.direction, r.direction);
	sphere.a = dot_vec3(r.direction, r.direction);
	//double b = 2.0 * dot_vec3(oc, r.direction);
	sphere.b = 2.0 * dot_vec3(sphere.oc, r.direction);
	//double c = dot_vec3(oc, oc) - ((obj->diameter) * (obj->diameter))/4;
	sphere.c = dot_vec3(sphere.oc, sphere.oc) - (obj->radius * obj->radius);
	//double discriminant = b * b - 4 * a * c;
	sphere.discriminant = sphere.b * sphere.b - 4 * sphere.a * sphere.c;
	//obj->t = INFINITY;
	//printf("Discriminant: %f\n", discriminant);
	//return (discriminant > 0);
	if (sphere.discriminant < 0)
		return (FALSE);
		//return 0;
	else
	{
		sphere.t0 = (-sphere.b - sqrt(sphere.discriminant) ) / (2.0 * sphere.a);
		sphere.t1 = (-sphere.b + sqrt(sphere.discriminant) ) / (2.0 * sphere.a);
		if(sphere.t0 < 0 && sphere.t1 < 0)
			return (FALSE);
		else if (sphere.t0 < 0.0)
			sphere.t0 = sphere.t1;
		else if (sphere.t1 < 0.0)
			sphere.t1 = sphere.t0;
		obj->t = fmin(sphere.t1, sphere.t0);
	}
	if (rec->t > obj->t && record)
	{
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
	return (TRUE);
}

double	hit_plane(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	double	denom;
	double	ret;
	t_vec3	normal;

	normal = obj->normal;
	//if (dot_vec3(r.direction, normal) > 0)
	//	normal = mul_double_vec3(-1, normal);
	denom = dot_vec3(r.direction, normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(obj->position, r.origin), obj->normal) / denom;
		if (ret < 1e-6)
			return (FALSE);
		else
			obj->t = ret;
		if (rec->t > obj->t && record)
		{
			rec->t = obj->t;
			rec->poi = get_intersect(r, obj->t);
			rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
			rec->obj = obj;
		}
	}
	return (TRUE);
}

//(q - pa - (va.q - pa)va)^2 - r^2 = 0
//where q is any point on cylinder, r.o + t * r.dir, point
//pa is position of cylinder in world, point
//va is normalized orientation of cylinder, vector
//(r.o + t * r.dir - pa - (va . (r.o + t * r.dir) - pa)va)^2 - r^2 = 0
//oc is point of ray.origin to coordinate of obj, delta.p

double	top_cap2(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_vec3	top;
	double	denom;
	double	ret;
	t_vec3 plane;
	
	top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	denom = dot_vec3(r.direction, obj->normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(top, r.origin), obj->normal) / denom;
		if (ret < 1e-6)
			return (FALSE);
		else
			obj->t = ret;
	}
	plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), top);
	if (dot_vec3(plane, plane) > (obj->radius * obj->radius))
		return (FALSE);
	if (rec->t > obj->t && record)
	{
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
	return (TRUE);
}

double	btm_cap2(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	double	denom;
	double	ret;
	t_vec3 plane;
	
	denom = dot_vec3(r.direction, obj->normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(obj->position, r.origin), obj->normal) / denom;
		if (ret < 1e-6)
			return (FALSE);
		else
			obj->t = ret;
	}
	plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), obj->position);
	if (dot_vec3(plane, plane) > (obj->radius * obj->radius))
		return (FALSE);
	if (rec->t > obj->t && record)
	{
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
	return (TRUE);
}

double	hit_cylinder2(t_object *obj, t_ray r, t_hit_record *rec, int record)
{
	t_cylinder2 cy;
	
	cy.top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	top_cap2(obj, r, rec, record);
	btm_cap2(obj, r, rec, record);
	cy.oc = sub_vec3(r.origin, obj->position);
	cy.a = dot_vec3(r.direction, r.direction) - (dot_vec3(r.direction, obj->normal)
				* dot_vec3(r.direction, obj->normal)) ;
	cy.b = 2.0 * (dot_vec3(r.direction, cy.oc) - (dot_vec3(r.direction, obj->normal)
				* dot_vec3(cy.oc, obj->normal)));
	cy.c = dot_vec3(cy.oc, cy.oc)
			- (dot_vec3(cy.oc,  obj->normal) * dot_vec3(cy.oc, obj->normal))
			- (obj->radius * obj->radius);
	cy.discriminant = cy.b * cy.b - 4 * cy.a * cy.c;
	if (cy.discriminant < 0)
		return (FALSE);
	else
	{
		cy.t0 = (-cy.b - sqrt(cy.discriminant) ) / (2.0 * cy.a);
		cy.t1 = (-cy.b + sqrt(cy.discriminant) ) / (2.0 * cy.a);
		if(cy.t0 < EPS && cy.t1 < EPS)
			return (FALSE);
		else if (cy.t0 > 0.0 && cy.t1 > 0.0)
			obj->t = fmin(cy.t1, cy.t0);
		else if (cy.t0 < 0.0)
			cy.t0 = cy.t1;
		else if (cy.t1 < 0.0)
			cy.t1 = cy.t0;
		obj->t = fmin(cy.t1, cy.t0);
	}
	if (dot_vec3(obj->normal, sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), cy.top)) > EPS)
		return (FALSE);
	else if (dot_vec3(obj->normal, sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), obj->position)) < EPS)
		return (FALSE);
	if (rec->t > obj->t && record)
	{
		rec->t = obj->t;
		rec->poi = get_intersect(r, obj->t);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->obj = obj;
	}
	return (TRUE);
}
