/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:21:49 by sulim             #+#    #+#             */
/*   Updated: 2023/08/15 13:46:20 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

unsigned int	rgb2color(t_vec3 color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	result;

	r = (unsigned int)(color.x);
	g = (unsigned int)(color.y);
	b = (unsigned int)(color.z);
	result = (r << 16) | (g << 8) | b;
	return (result);
}

t_ray	get_ray(double u, double v, t_mlx *rt)
{
	t_ray	ray;

	ray.origin = rt->scene.camera.position;
	ray.direction = normalize(sub_vec3(add_vec3(\
	add_vec3(rt->scene.camera.vars.llc, mul_double_vec3(u, \
	rt->scene.camera.vars.horizontal)), mul_double_vec3(v, \
	rt->scene.camera.vars.vertical)), ray.origin));
	return (ray);
}

	//t_mat44 translation;
	//t_mat44 rotation;
void	init_cam(t_mlx *rt)
{
	t_camera	*camray;

	camray = &(rt->scene.camera);
	if (rt->rotated)
	{
		camray->vars.forward = normalize(sub_vec3(vec3(0, 0, 0), \
		camray->direction));
		camray->vars.right = normalize(cross_vec3(get_up(camray->vars.forward), \
		camray->vars.forward));
		camray->vars.up = normalize(cross_vec3(camray->vars.right, \
		camray->direction));
		rt->rotated = FALSE;
	}
	camray->vars.horizontal = mul_double_vec3(camray->vars.view_w, \
	camray->vars.right);
	camray->vars.vertical = mul_double_vec3(camray->vars.view_h, \
	camray->vars.up);
	camray->vars.llc = sub_vec3(sub_vec3(sub_vec3(camray->position, \
	div_double_vec3(2.0, camray->vars.horizontal)), div_double_vec3(2.0, \
	camray->vars.vertical)), camray->vars.forward);
}
	//camray->vars.aspect_r = (double)rt->win_width / (double)rt->win_height;
	//camray->vars.h = tan((degtorad(camray->vars.fov)/2));
	//camray->vars.view_h = 2.0 * camray->vars.h;
	//camray->vars.view_w = camray->vars.aspect_r * camray->vars.view_h;

	//get_translation(camray->position, &translation);
	//get_rotation(camray, &rotation);
	//camray->camtoworld = add_mat(translation, rotation);
