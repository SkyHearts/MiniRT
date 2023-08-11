/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:01:29 by sulim             #+#    #+#             */
/*   Updated: 2023/08/11 15:20:33 by sulim            ###   ########.fr       */
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
	length(sub_vec3(light->position, rec.poi)))
		return (1);
	return (0);
}

t_vec3	get_specular(t_ray camray, t_hit_record	rec, t_light *current_light)
{
	t_vec3			view_direction;
	t_vec3			reflect_direction;
	double			spec;

	view_direction = normalize(sub_vec3(camray.direction, rec.obj->position));
	reflect_direction = reflect(mul_double_vec3(-1, rec.light_direction), \
	mul_double_vec3(1, rec.normal));
	spec = pow(fmax(dot_vec3(view_direction, reflect_direction), 0), 32);
	return (mul_double_vec3((SPECULAR_STRENGTH * spec), current_light->color));
}

t_vec3	calc_color(t_scene *sc, t_hit_record rec, t_vec3 amb, t_ray camray)
{
	t_light			*light;
	color			ret;
	double			cosine;
	t_vec3			specular;
	t_vec3			min;
	t_vec3			shadow;

	ret.color = vec3(0, 0, 0);
	light = sc->light;
	while (light != NULL)
	{
		rec.light_direction = normalize(sub_vec3(light->position, rec.poi));
		if (shade(sc, rec, light, camray))
		{
			shadow = vec3(0, 0, 0);
			shadow = add_vec3(shadow, amb);
			ret.color = shadow;
		}
		else
		{
			cosine = dot_vec3(rec.light_direction, rec.normal);
			specular = get_specular(camray, rec, light);
			if (cosine > 0)
			{
				min = add_vec3(ret.color, amb);
				ret.color = add_vec3(specular, mul_double_vec3(light->ratio, \
				mul_double_vec3(fmax(0.0, cosine), rec.obj->color)));
				ret = clamp_vec(&ret, min, 255);
			}
		}
		light = light->next;
	}
	return (ret.color);
}

color	ray_color(t_scene *sc, t_ray camray)
{
	t_hit_record	rec;
	color			pixel_color;
	t_vec3			amb;
	t_vec3			min;

	pixel_color.color = vec3(0, 0, 0);
	min = vec3(0, 0, 0);
	if (hit_object(camray, sc->object, &rec, 1) > 0)
	{
		amb = mul_double_vec3(sc->ambient.ratio, mul_vec3(rec.obj->color, \
		div_double_vec3(255, sc->ambient.color)));
		pixel_color.color = calc_color(sc, rec, amb, camray);
	}
	else
		pixel_color.color = mul_double_vec3(sc->ambient.ratio, \
		sc->ambient.color);
	return (clamp_vec(&pixel_color, min, 255));
}