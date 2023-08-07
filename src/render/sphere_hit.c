/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:08:57 by jyim              #+#    #+#             */
/*   Updated: 2023/08/07 18:55:22 by jyim             ###   ########.fr       */
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
	{
		normal = object->normal;
		//if (dot_vec3(r.direction, normal) > 0)
		//	normal = mul_double_vec3(-1, normal);
	}
	if (object->type == 2)
	{
		height = dot_vec3(normalize(object->normal), sub_vec3(poi, object->position));
		normal = normalize(sub_vec3(poi, add_vec3(object->position, mul_double_vec3(height, object->normal))));
		if (dot_vec3(r.direction, normal) > 0.0)
			normal = mul_double_vec3(-1, normal);
	}
	return (normal);
}

double	hit_sphere(t_object *obj, t_ray r, t_hit_record *rec)
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
	if (rec->t > obj->t)
	{
		rec->poi = get_intersect(r, obj->t);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->t = obj->t;
		rec->obj = obj;
	}
	return (TRUE);
}

double	hit_plane(t_object *obj, t_ray r, t_hit_record *rec)
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
		if (rec->t > obj->t)
		{
			rec->poi = get_intersect(r, obj->t);
			rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
			rec->t = obj->t;
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
double	hit_cylinder(t_object *obj, t_ray r)
{
	t_vec3	top;
	top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	//t_vec3 oc = sub_vec3(r.origin, obj->position); //delta.p
	double	dot_raynormal = dot_vec3(r.direction, obj->normal);	//dot(ray.dir, 	obj.normal)
	t_vec3 cy = sub_vec3(r.direction, mul_double_vec3(dot_raynormal, obj->normal));
	t_vec3 delta_p = sub_vec3(r.origin, obj->position);
	t_vec3 cy_normal = sub_vec3(delta_p, mul_double_vec3(dot_vec3(delta_p, obj->normal), obj->normal));
	double a = dot_vec3(cy, cy);
	double b = 2.0 * dot_vec3(cy, cy_normal);
	double c = dot_vec3(cy_normal, cy_normal) - ((obj->diameter) * (obj->diameter)) / 4;
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (FALSE);
	//	//return 0;
	else
	{
		double t0 = (-b - sqrt(discriminant) ) / (2.0 * a);
		double t1 = (-b + sqrt(discriminant) ) / (2.0 * a);
		//printf("t0: %f\n",t0);
		//printf("t1: %f\n",t1);
		if(t0 < 0 && t1 < 0)
		{
			obj->t =  -1.0;
		}
		else if (t0 > 0.0 && t1 > 0.0)
			obj->t = fmin(t1, t0);
		else if (t0 < 0.0)
			t0 = t1;
		else if (t1 < 0.0)
			t1 = t0;
		//if (t1 < 0)
		//	obj->t = (t0 > 0 ? t0 : t1);
		obj->t = fmin(t1, t0);
	}
	if (dot_vec3(obj->normal, normalize(sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), top))) > 0)
		obj->t = -1;
		//top_cap(obj, r);
	else if (dot_vec3(obj->normal, normalize(sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), obj->position))) < 0)
		obj->t = -1;
		//btm_cap(obj, r);
	//hit_top_cap(obj, r);
	//hit_btm_cap(obj, r);
	return obj->t;
}


//(q- p1)2 < r2
//
double	top_cap(t_object *obj, t_ray r)
{
	t_vec3	top;
	double	denom;
	top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	//t_vec3 delta_p = sub_vec3(r.origin, top);
	denom = dot_vec3(r.direction, obj->normal);
	double	ret;
	//t_vec3	normal;
	//if (dot_vec3(r.direction, normal) > 0)
	//	normal = mul_double_vec3(-1, normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(top, r.origin), obj->normal) / denom;
		if (ret > 0)
			obj->t = ret;
	}
	t_vec3 plane;
	plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), top);
	if (dot_vec3(plane, plane) > (obj->radius * obj->radius))
		return (FALSE);
	return (TRUE);
}

double	btm_cap(t_object *obj, t_ray r)
{
	double	denom;
	//t_vec3 delta_p = sub_vec3(r.origin, top);
	double	ret;
	t_vec3	normal;
	normal = obj->normal;
	if (dot_vec3(r.direction, normal) > 0)
		normal = mul_double_vec3(-1, normal);
	denom = dot_vec3(r.direction, normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(obj->position, r.origin), normal) / denom;
		if (ret > 0)
		{
			obj->t = ret;
		}
	}
	t_vec3 plane;
	plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), normal);
	if (dot_vec3(plane, plane) > (((obj->diameter) * (obj->diameter)) / 4))
		obj->t = -1;
	return (obj->t);
}

double	top_cap2(t_object *obj, t_ray r, t_hit_record *rec)
{
	t_vec3	top;
	double	denom;
	top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	//t_vec3 delta_p = sub_vec3(r.origin, top);
	denom = dot_vec3(r.direction, obj->normal);
	double	ret;
	//t_vec3	normal;
	//if (dot_vec3(r.direction, normal) > 0)
	//	normal = mul_double_vec3(-1, normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(top, r.origin), obj->normal) / denom;
		if (ret < 1e-6)
			return (FALSE);
		else
			obj->t = ret;
	}
	t_vec3 plane;
	plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), top);
	if (dot_vec3(plane, plane) > (obj->radius * obj->radius))
		return (FALSE);
	if (rec->t > obj->t)
	{
		rec->poi = get_intersect(r, obj->t);
		//rec->normal = obj->normal;
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->t = obj->t;
		rec->obj = obj;
	}
	return (TRUE);
}

double	btm_cap2(t_object *obj, t_ray r, t_hit_record *rec)
{
	//t_vec3	top;
	double	denom;
	//top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	//t_vec3 delta_p = sub_vec3(r.origin, top);
	denom = dot_vec3(r.direction, obj->normal);
	double	ret;
	//t_vec3	normal;
	//if (dot_vec3(r.direction, normal) > 0)
	//	normal = mul_double_vec3(-1, normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(obj->position, r.origin), obj->normal) / denom;
		if (ret < 1e-6)
			return (FALSE);
		else
			obj->t = ret;
	}
	t_vec3 plane;
	plane = sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), obj->position);
	if (dot_vec3(plane, plane) > (obj->radius * obj->radius))
		return (FALSE);
	if (rec->t > obj->t)
	{
		rec->poi = get_intersect(r, obj->t);
		//rec->normal = obj->normal;
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->t = obj->t;
		rec->obj = obj;
	}
	return (TRUE);
}

double	hit_cylinder2(t_object *obj, t_ray r, t_hit_record *rec)
{
	t_cylinder2 cy;
	top_cap2(obj, r, rec);
	btm_cap2(obj, r, rec);
	cy.top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
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
		if(cy.t0 < 0 && cy.t1 < 0)
			return (FALSE);
		else if (cy.t0 > 0.0 && cy.t1 > 0.0)
			obj->t = fmin(cy.t1, cy.t0);
		else if (cy.t0 < 0.0)
			cy.t0 = cy.t1;
		else if (cy.t1 < 0.0)
			cy.t1 = cy.t0;
		obj->t = fmin(cy.t1, cy.t0);
	}
	if (dot_vec3(obj->normal, sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), cy.top)) > 0)
		return (FALSE);
		//top_cap2(obj, r, rec);
	else if (dot_vec3(obj->normal, sub_vec3(add_vec3(r.origin, mul_double_vec3(obj->t, r.direction)), obj->position)) < 0)
		return (FALSE);
		//btm_cap2(obj, r, rec);
	if (rec->t > obj->t)
	{
		rec->poi = get_intersect(r, obj->t);
		rec->normal = get_obj_normal2(r, obj, rec, rec->poi);
		rec->t = obj->t;
		rec->obj = obj;
	}
	return (TRUE);
}
