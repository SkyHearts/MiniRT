/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:42:51 by jyim              #+#    #+#             */
/*   Updated: 2023/07/20 12:42:51 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include "../../inc/scene.h"
#include "../../inc/camera.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

/* 
Add ambient input into scene
Only 1 input is allowed
if additional input, return 1
 */
int	add_ambient(char **split, t_mlx *rt)
{
	t_scene	s;
	char	**color;

	s = rt->scene;
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	if (s.ambient.filled == 1)
		return (1); 	// print error then return 1, Multiple ambient input
	s.ambient.ratio = ft_atof(split[1]);
	color = ft_split(split[2], ',');
	s.ambient.color.x = atoi(color[0]);
	s.ambient.color.y = atoi(color[1]);
	s.ambient.color.z = atoi(color[2]);
	s.ambient.filled = 1;
	return (free_darray(split), free_darray(color), 0);
}

int	add_camera(char **split, t_mlx *rt)
{
	t_scene	s;
	t_camera cam;
	char **pos;
	char **ori;
	
	s = rt->scene;
	cam = rt->scene.camera;
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	if (cam.filled == 1)
		return (1); 	// print error then return 1, Multiple camera input
	pos = ft_split(split[1], ',');
	cam.position.x = atof(pos[0]);
	cam.position.y = atof(pos[1]);
	cam.position.z = atof(pos[2]);
	ori = ft_split(split[2], ',');
	cam.direction.x = atof(ori[0]);
	cam.direction.y = atof(ori[1]);
	cam.direction.z = atof(ori[2]);
	cam.filled = 1;
	return (free_darray(split), free_darray(pos), free_darray(ori), 0);
}

int	add_light(char **split, t_mlx *rt)
{
	t_light *lights;

	lights = rt->scene.light;
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	if (!lights)
		lights = ft_newlight(split);
	else
		ft_lightadd_back(lights, ft_newlight(split));
	return (free_darray(split), 0);
}

int	add_sphere(char **split, t_mlx *rt)
{
	t_object *obj;

	obj = rt->scene.object;
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	if (!obj)
		obj = ft_newobj(split);
	else
		ft_lightadd_back(obj, ft_newlight(split));
	return (free_darray(split), 0);
}

// "A C L sp pl cy"
int	parse_line (t_mlx *rt, char *line)
{
	char **split;
	int ret;

	split = ft_split(line, ' ');
	if (!ft_strcmp_wlist(split[0], rt->element))
		return (1);
	if (!ft_strcmp(split[0], "A"))
		ret = add_ambient(split, rt);
	else if (!ft_strcmp(split[0], "C"))
		ret = add_camera(split, rt);
	else if (!ft_strcmp(split[0], "L"))
		ret = add_light(split, rt);
	else if (!ft_strcmp(split[0], "sp"))
		ret = add_sphere(split, rt);
	else if (!ft_strcmp(split[0], "pl"))
		ret = add_plane();
	else if (!ft_strcmp(split[0], "cy"))
		ret = add_cylinder();
	return (ret);
}

int check_ext(char *file)
{
	char *tmp;
	
	tmp = ft_strrchr(file, '.');
	if (tmp != NULL)
		if (!ft_strcmp(tmp, ".rt"))
			return (0);
	return (1);
}

int	parse_scene(char *file, t_mlx *rt)
{
	int fd;
	int ret;
	char *line;

	if (check_ext(file));
		return (1);
	fd = open_file(file);
	line = get_next_line(fd);
	if (!line)
		// error empty file, return 1
	while (line)
	{
		ret = parse_line(rt, line);
		if (ret > 0)
			break ;
		line = get_next_line(fd);
	}
	return (ret);
}