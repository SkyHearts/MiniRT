/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:32:44 by jyim              #+#    #+#             */
/*   Updated: 2023/08/12 13:19:56 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

/* 
Add ambient input into scene
Only 1 input is allowed
if additional input, return 1
 */
// print error then return 1,
// element format wrong @goto int check_format(char **split)
// print error then return 1, Multiple ambient input
// print error then return 1,
//Input range incorrect "element split[0] incorrect range input"
int	add_ambient(char **split, t_mlx *rt)
{
	t_scene	*s;

	s = &(rt->scene);
	if (check_format(split))
		return (printf("Element format wrong\n"), 1);
	if (s->ambient.filled == 1)
		return (printf("Multiple ambient input\n"), 1);
	s->ambient.ratio = ft_atof(split[1]);
	s->ambient.color = get_color(split[2]);
	s->ambient.filled = 1;
	if (check_col_range(s->ambient.color) || check_range(s->ambient.ratio, 1))
		return (1);
	return (0);
}

static void	cam_init(t_camera *cam, char **split, t_mlx *rt)
{
	cam->position = get_coordinate(split[1]);
	cam->direction = get_coordinate(split[2]);
	cam->vars.fov = ft_atoi(split[3]);
	cam->vars.aspect_r = (double)rt->win_width / (double)rt->win_height;
	cam->vars.forward = normalize(sub_vec3(vec3(0, 0, 0), cam->direction));
	cam->vars.right = cross_vec3(get_up(cam->vars.forward), cam->vars.forward);
	cam->vars.up = normalize(cross_vec3(cam->vars.right, cam->direction));
	cam->vars.right = cross_vec3(cam->vars.up, cam->vars.forward);
	cam->vars.h = tan((degtorad(cam->vars.fov) / 2));
	cam->vars.view_h = 2.0 * cam->vars.h;
	cam->vars.view_w = cam->vars.aspect_r * cam->vars.view_h;
	cam->vars.horizontal = mul_double_vec3(cam->vars.view_w, cam->vars.right);
	cam->vars.vertical = mul_double_vec3(cam->vars.view_h, cam->vars.up);
	cam->vars.llc = sub_vec3(sub_vec3(sub_vec3(cam->position,
					div_double_vec3(2.0, cam->vars.horizontal)),
				div_double_vec3(2.0, cam->vars.vertical)), cam->vars.forward);
}

// print error then return 1,
// element format wrong @goto int check_format(char **split)
// print error then return 1, Multiple camera input
// init_cam(rt);
// print error then return 1, Input range incorrect
int	add_camera(char **split, t_mlx *rt)
{
	t_camera	*cam;

	cam = &(rt->scene.camera);
	if (check_format(split))
		return (1);
	if (cam->filled == 1)
		return (printf("Multiple camera input\n"), 1);
	cam_init(cam, split, rt);
	cam->filled = 1;
	if (check_range(cam->vars.fov, 3))
		return (1);
	return (0);
}

// print error then return 1,
// element format wrong @goto int check_format(char **split)
// print error then return 1,
// input range incorrect
int	add_light(char **split, t_mlx *rt)
{
	t_light	**lights;
	t_light	*new_lights;

	lights = &(rt->scene.light);
	if (check_format(split))
		return (1);
	else
	{
		new_lights = ft_newlight(split);
		ft_lightadd_back(lights, new_lights);
	}
	if (check_col_range(new_lights->color) || check_range(new_lights->ratio, 1))
		return (1);
	return (0);
}

// print error then return 1,
// element format wrong @goto int check_format(char **split)
// print error then return 1,
// input range incorrect
int	add_obj(char **split, t_mlx *rt)
{
	t_object	**obj;
	t_object	*new_obj;

	obj = &(rt->scene.object);
	if (check_format(split))
		return (1);
	else
	{
		new_obj = ft_newobj(split);
		ft_objadd_back(obj, new_obj);
	}
	if (check_col_range(new_obj->color))
		return (1);
	return (0);
}
