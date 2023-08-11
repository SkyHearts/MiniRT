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

// "A C L sp pl cy"
// Unknow element detected, return 1
int	parse_line(t_mlx *rt, char *line)
{
	char	**split;
	int		ret;

	split = isspace_split(line);
	if (isempty(line) || line[0] == '#')
		return (free_darray(split), 0);
	if (!ft_strcmp_wlist(split[0], rt->element))
		return (printf("File error: Unknown element\n"), free_darray(split), 1);
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

// File not found or Wrong extension error, return 1
// error empty file, return 1
int	parse_scene(char *file, t_mlx *rt)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open_file(file);
	ret = 0;
	if (fd < 0 || check_ext(file))
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (printf("File error: Empty file\n"), 1);
	while (line)
	{
		ret = parse_line(rt, line);
		if (ret > 0)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!rt->scene.ambient.filled || !rt->scene.camera.filled)
		return (printf("Ambient, camera or lights not inserted\n"), 0);
	rt->scene.act_light = rt->scene.light;
	return (ret);
}
