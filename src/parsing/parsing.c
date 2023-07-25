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
	t_scene	*s;

	s = &(rt->scene);
	if (check_format(split))
		return (printf("Element format wrong\n"),1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	if (s->ambient.filled == 1)
		return (printf("Multiple ambient input\n"), 1); 	// print error then return 1, Multiple ambient input
	s->ambient.ratio = ft_atof(split[1]);
	s->ambient.color = get_color(split[2]);
	s->ambient.filled = 1;
	if (check_col_range(s->ambient.color) || check_range(s->ambient.ratio, 1))
		return (1);  // print error then return 1, Input range incorrect "element split[0] incorrect range input"
	return (0);
}

int	add_camera(char **split, t_mlx *rt)
{
	t_scene	s;
	t_camera *cam;
	
	s = rt->scene;
	cam = &(rt->scene.camera);
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	if (cam->filled == 1)
		return (printf("Multiple camera input\n"), 1); 	// print error then return 1, Multiple camera input
	cam->position = get_coordinate(split[1]);
	cam->direction = get_coordinate(split[2]);
	cam->vars.fov = ft_atoi(split[3]);
	cam->filled = 1;
	//init_cam(rt);
	if (check_range(cam->vars.fov, 3))
		return (1);  // print error then return 1, Input range incorrect
	return (0);
}

int	add_light(char **split, t_mlx *rt)
{
	t_light **lights;
	t_light *new_lights;

	lights = &(rt->scene.light);
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	else
	{
		new_lights = ft_newlight(split);
		ft_lightadd_back(lights, new_lights);
	}
	if (check_col_range(new_lights->color) || check_range(new_lights->ratio, 1))
		return (1); // print error then return 1, input range incorrect
	return (0);
}

int	add_obj(char **split, t_mlx *rt)
{
	t_object **obj;
	t_object *new_obj;

	obj = &(rt->scene.object);
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)
	else
	{
		new_obj = ft_newobj(split);
		ft_objadd_back(obj, new_obj);
	}
	if (check_col_range(new_obj->color))
		return (1); // print error then return 1, input range incorrect
	return (0);
}

// "A C L sp pl cy"
int	parse_line(t_mlx *rt, char *line)
{
	char **split;
	int ret;

	split = isspace_split(line);
	if (isempty(line))
		return (free_darray(split), 0);
	if (!ft_strcmp_wlist(split[0], rt->element))
		return (printf("File error: Unknown element\n"), free_darray(split), 1); // Unknow element detected, return 1
	if (!ft_strcmp(split[0], "A"))
		ret = add_ambient(split, rt);
	else if (!ft_strcmp(split[0], "C"))
		ret = add_camera(split, rt);
	else if (!ft_strcmp(split[0], "L"))
		ret = add_light(split, rt);
	else
		ret = add_obj(split, rt);
	return (free_darray(split), ret);
}

int check_ext(char *file)
{
	char *tmp;
	
	tmp = ft_strrchr(file, '.');
	if (tmp != NULL)
		if (!ft_strcmp(tmp, ".rt"))
			return (0);
	ft_printf("File error: Invalid file extention\n");
	return (1); // print error here, wrong extension
}

int	parse_scene(char *file, t_mlx *rt)
{
	int fd;
	int ret;
	char *line;
	//int i = 0;

	fd = open_file(file);
	ret = 0;
	if (fd < 0 || check_ext(file))
		return (1); // File not found or Wrong extension error, return 1
	line = get_next_line(fd);
	if (!line)
		return(ft_printf("File error: Empty file\n"), 1); // error empty file, return 1
	while (line)
	{
		//printf("Pass %d\n", ++i);
		ret = parse_line(rt, line);
		//printf("ret: %d\n", ret);
		if (ret > 0)
			break ;
		free(line);	
		line = get_next_line(fd);
	}
	if (!rt->scene.ambient.filled || !rt->scene.camera.filled)
		return (0);
	return (ret);
}
