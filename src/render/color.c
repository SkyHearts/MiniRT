/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:01:29 by sulim             #+#    #+#             */
/*   Updated: 2023/08/11 21:13:44 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

int	shade(t_scene *sc, t_hit_record rec, t_light *light, t_ray camray)
{
	t_ray			shadowray;
	t_hit_record	shadow_rec;

	shadowray.direction = rec.light_direction;
	shadowray.origin = get_shadow_origin(&rec);
	if (hit_object(shadowray, sc->object, &shadow_rec, 1) > 0 && \
	dot_vec3(camray.direction, rec.normal) < 0.0 && shadow_rec.t < \
	length(sub_vec3(light->position, rec.poi)) && shadow_rec.t > EPS)
		return (1);
	return (0);
}

t_vec3	specular(t_ray camray, t_hit_record	rec, t_light *current_light)
{
	t_vec3			view_direction;
	t_vec3			reflect_direction;
	double			spec;

	view_direction = normalize(sub_vec3(camray.origin, rec.poi));
	reflect_direction = reflect(mul_double_vec3(-1, rec.light_direction), \
	mul_double_vec3(1, rec.normal));
	spec = pow(fmax(dot_vec3(view_direction, reflect_direction), 0), 32);
	return (mul_double_vec3((SPECULAR_STRENGTH * current_light->ratio * spec), \
	current_light->color));
}

t_vec3	calc_color(t_scene *sc, t_hit_record rec, t_vec3 amb, t_ray camray)
{
	t_light			*l;
	double			d;

	rec.ret.color = vec3(0, 0, 0);
	l = sc->light;
	while (l != NULL)
	{
		rec.light_direction = normalize(sub_vec3(l->position, rec.poi));
		if (shade(sc, rec, l, camray))
			rec.ret.color = add_vec3(rec.ret.color, amb);
		else
		{
			d = dot_vec3(rec.light_direction, rec.normal);
			if (d > 0)
			{
				rec.min = add_vec3(rec.ret.color, amb);
				rec.ret.color = add_vec3(specular(camray, rec, l), \
				mul_double_vec3(l->ratio, mul_double_vec3(d, rec.obj->color)));
				rec.ret = clamp_vec(&rec.ret, rec.min, 255.0);
			}
			rec.ret.color = add_vec3(rec.ret.color, amb);
		}
		l = l->next;
	}
	return (rec.ret.color);
}

color	ray_color(t_scene *sc, t_ray camray)
{
	t_hit_record	rec;
	t_vec3			amb;

	rec.min = vec3(0, 0, 0);
	if (hit_object(camray, sc->object, &rec, 1) > 0)
	{
		amb = mul_double_vec3(sc->ambient.ratio, mul_vec3(rec.obj->color, \
		div_double_vec3(255.0, sc->ambient.color)));
		rec.ret.color = calc_color(sc, rec, amb, camray);
	}
	else
		rec.ret.color = mul_double_vec3(sc->ambient.ratio, \
		sc->ambient.color);
	return (clamp_vec(&rec.ret, rec.min, 255.0));
}
