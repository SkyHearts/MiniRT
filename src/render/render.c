/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:08 by jyim              #+#    #+#             */
/*   Updated: 2023/08/11 15:18:33 by jyim             ###   ########.fr       */
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

void	print_cam_debug(t_mlx *rt)
{
	printf("CAMERA BEFORE RENDER\n");
	printf("Position: ");
	printvec_nl((*rt).scene.camera.position);
	printf("Forward: ");
	printvec_nl(rt->scene.camera.vars.forward);
	printf("Right: ");
	printvec_nl(rt->scene.camera.vars.right);
	printf("Up: ");
	printvec_nl(rt->scene.camera.vars.up);
	printf("Aspect Ratio: %f\n", rt->scene.camera.vars.aspect_r);
	printf("fov: %f\n", rt->scene.camera.vars.fov);
	printf("h: %f\n", rt->scene.camera.vars.h);
	printf("View_h: %f\n", rt->scene.camera.vars.view_h);
	printf("View_w: %f\n", rt->scene.camera.vars.view_w);
	printf("Lower Left Coner: ");
	printvec_nl(rt->scene.camera.vars.llc);
	//printf("Camera to world matrix: \n");
	//print_matrix(rt->scene.camera.camtoworld);
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

void	render(t_mlx *rt)
{
	int			x;
	int			y;
	int			step;
	t_object	*obj;
	color		pixel_color;

	if (rt->mode == 1)
		step = 4;
	else
		step = 1;
	y = rt->win_height - 1;
	ft_memset(rt->addr, 0, ((rt->win_height * rt->line_length) + (rt->win_width \
	* (rt->bpp / 8))));
	init_cam(rt);
	obj = rt->scene.object;
	while (y >= 0)
	{
		x = 0;
		while (x < rt->win_width)
		{
			t_ray	camray;

			double u = (double)x / (rt->win_width - 1);
			double v = (double)y / (rt->win_height - 1);
			camray = get_ray(u, v, rt);
			//write ray data for debug
			pixel_color = ray_color(&rt->scene, camray);
			img_mlx_pixel_put(rt, x, y, rgb2color(pixel_color.color));
			//img_mlx_pixel_put(rt, x, y, 0xffffff);
			x += step;
		}
		y -= step;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
}
