/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:40:48 by jyim              #+#    #+#             */
/*   Updated: 2023/08/08 12:56:34 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//All written unused or backup codes are inserted here
#include "../inc/minirt.h"

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
	double	ret;
	t_vec3 plane;
	
	top = add_vec3(obj->position, mul_double_vec3(obj->height, obj->normal));
	denom = dot_vec3(r.direction, obj->normal);
	if (fabs(denom) > 1e-6)
	{
		ret = dot_vec3(sub_vec3(top, r.origin), obj->normal) / denom;
		if (ret > 0)
			obj->t = ret;
	}
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

double	hit_sphere(t_object *obj, t_ray r, t_hit_record *rec)
{
	//center = sphere centre, radius = sphere radius
	//write data for debug
	obj->t = -1;
	t_vec3 oc = sub_vec3(r.origin, obj->position);
	double a = dot_vec3(r.direction, r.direction);
	double b = 2.0 * dot_vec3(oc, r.direction);
	double c = dot_vec3(oc, oc) - ((obj->diameter) * (obj->diameter))/4;
	double discriminant = b * b - 4 * a * c;
	obj->t = INFINITY;
	printf("Discriminant: %f\n", discriminant);
	return (discriminant > 0);
	if (discriminant < 0)
		return (FALSE);
		//return 0;
	else
	{
		double t0 = (-b - sqrt(discriminant) ) / (2.0 * a);
		double t1 = (-b + sqrt(discriminant) ) / (2.0 * a);
		if(t0 < 0 && t1 < 0)
			return (FALSE);
		else if (t0 < 0.0)
			t0 = t1;
		else if (t1 < 0.0)
			t1 = t0;
		obj->t = fmin(t1, t0);
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

int	hit_object(t_ray r, t_object *obj, t_hit_record *rec)
{
	int			hit;
	t_object	*current_obj;
	hit = 0;
	current_obj = obj;
	rec->t = INFINITY;
	//(void) rec;
	
	while (current_obj != NULL)
	{
		if (current_obj->type == 0)
			hit = hit_sphere(current_obj, r, rec);
		else if (current_obj->type == 1)
			hit = hit_plane(current_obj, r, rec);
		else if (current_obj->type == 2)
		{
		 	hit = hit_cylinder2(current_obj, r, rec);
			//top_cap(current_obj, r);
		}
		//if (rec->t > current_obj->t && current_obj->t != -1)
		//{
		//	rec->t = current_obj->t;
		//	rec->obj = current_obj;
		//	// printf("Obj type: %d\n", rec.obj->type);
		//	// printf("Obj color:");
		//	// printvec_nl(rec.obj->color);
		//}
		current_obj = current_obj->next;
	}
	if (rec->t == INFINITY)
		rec->t = -1;
	return (rec->t);
} 

int	inlight(t_vec3 poi, t_object *object, t_light *light)
{
	double	light_dis;
	double	intersect_dis;

	light_dis = length(sub_vec3(poi, light->position));
	intersect_dis = length(sub_vec3(poi, object->position));
	if (light_dis < intersect_dis)
		return (1);
	return (0);
}

color ray_color(t_object *object, t_ray camray, t_light *light, t_mlx *rt)
{
	color			pixel_color;
	t_vec3			light_direction;
	//t_vec3			obj_normal;
	t_light			*current_light;
	t_hit_record	rec;
	double			cosine;

	double			specular_strength;
	t_vec3			view_direction;
	t_vec3			reflect_direction;
	double			spec;
	t_vec3			specular;
	color			white_color;

	(void)rt;
	specular_strength = 0.5;
	pixel_color.color = vec3(0,0,0);
	white_color.color = vec3(255,255,255);
	current_light = light;
	//rec.t = INFINITY;

	if (hit_object(camray, object, &rec) > 0)
	{
		while (current_light != NULL)
		{
			//obj_normal = get_obj_normal(camray, rec.obj, current_light);
			//light_direction = normalize(sub_vec3(current_light->position, add_vec3(camray.origin, mul_double_vec3(rec.t, camray.direction))));
			//light_direction = getlightdir(camray, current_light, &rec);
			light_direction = normalize(sub_vec3(current_light->position, rec.poi));
			cosine = dot_vec3(light_direction, rec.normal);
			view_direction = normalize(sub_vec3(camray.direction, rec.obj->position));
			reflect_direction = reflect(mul_double_vec3(-1, light_direction), mul_double_vec3(1, rec.normal));
			spec = pow(fmax(dot_vec3(view_direction, reflect_direction), 0), 32);
			specular = mul_double_vec3((specular_strength * spec), current_light->color);
			if (cosine < 0)
				//pixel_color.color = ambient(&rec, rt);
				break;
			else
				// pixel_color.color = mul_double_vec3(light->ratio, mul_double_vec3(cosine, rec.obj->color));
				pixel_color.color = add_vec3(specular, mul_double_vec3(light->ratio, mul_double_vec3(fmax(0.0, cosine), rec.obj->color)));
				// pixel_color.color = mul_double_vec3(light->ratio, mul_double_vec3(cosine, rec.obj->color));
				//pixel_color.color = (rec.obj->color);
			current_light = current_light->next;
		}	
	}
	return (clamp_vec(&pixel_color, 0.0, 255.0));
}