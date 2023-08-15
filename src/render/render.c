/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:08 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 12:39:27 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

t_vec3	get_up(t_vec3 orientation)
{
	if (orientation.y == 1.0)
		return (vec3(0, 0, 1));
	if (orientation.y == -1.0)
		return (vec3(0, 0, -1));
	return (vec3(0, 1, 0));
}

double	degtorad(double theta)
{
	double	rad;

	rad = theta * (M_PI / 180);
	return (rad);
}

t_vec3	getlightdir(t_ray camray, t_light *light, t_hit_record *rec)
{
	t_vec3	light_direction;

	light_direction = normalize(sub_vec3(light->position, \
	add_vec3(camray.origin, mul_double_vec3(rec->t, camray.direction))));
	if (dot_vec3(camray.direction, light_direction) > 0.0)
		light_direction = normalize(mul_double_vec3(-1, light_direction));
	return (light_direction);
}

void	render_color(t_mlx *rt, t_counter count)
{
	t_ray		camray;
	t_color		pixel_color;
	double		u;
	double		v;

	u = (double)count.x / (rt->win_width - 1);
	v = (double)count.y / (rt->win_height - 1);
	camray = get_ray(u, v, rt);
	pixel_color = ray_color(&rt->scene, camray);
	img_mlx_pixel_put(rt, count.x, count.y, rgb2color(pixel_color.color));
}

void	render(t_mlx *rt)
{
	t_counter	count;
	t_object	*obj;

	if (rt->mode == 1)
		count.step = 4;
	else
		count.step = 1;
	count.y = rt->win_height - 1;
	ft_memset(rt->addr, 0, ((rt->win_height * rt->line_length) + (rt->win_width \
	* (rt->bpp / 8))));
	init_cam(rt);
	obj = rt->scene.object;
	while (count.y >= 0)
	{
		count.x = 0;
		printf("\33[1F\33[2KScanlines remaining : %d\n", count.y);
		while (count.x < rt->win_width)
		{
			render_color(rt, count);
			count.x += count.step;
		}
		count.y -= count.step;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
}
			//write ray data for debug
			//img_mlx_pixel_put(rt, x, y, 0xffffff);
