/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:59:11 by jyim              #+#    #+#             */
/*   Updated: 2023/07/18 17:59:11 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "../inc/scene.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int open_file(char *file)
{
	int fd;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("File error");
	return (fd);
		
}

int ft_strcmp_clist(char *line, char *cmp)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (cmp[j])
		{
			if (line[i] == cmp[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// "A C L sp pl cy"
int ft_strcmp_wlist(char *line, char **cmp)
{
	int i;
	int j;

	i = 0;
	while (cmp[i])
	{
		if (!ft_strcmp(line, cmp[i]))
			return (1);
		i++;
	}
	return (0);
}
int	add_ambient(char **split, t_mlx *rt)
{
	t_scene s;
	int	len;

	s = rt->scene;
	len = split_len(split);
	if (len != 3)
		return (1)
	s.ambient = 
}
// "A C L sp pl cy"
int	parse_line (t_mlx *rt, char *line)
{
	char **split;
	int ret;

	split = ft_split(line);
	if (!ft_strcmp_wlist(split[0], rt->element))
		return (1);
	if (!ft_strcmp(split[0], "A"))
		ret = add_ambient(split, rt);
	else if (!ft_strcmp(split[0], "C"))
		ret = add_camera();
	else if (!ft_strcmp(split[0], "L"))
		ret = add_light();
	else if (!ft_strcmp(split[0], "sp"))
		ret = add_sphere();
	else if (!ft_strcmp(split[0], "pl"))
		ret = add_plane();
	else if (!ft_strcmp(split[0], "cy"))
		ret = add_cylinder();
	return (ret);
}

int	parse_scene(char *file, t_mlx *rt)
{
	int fd;
	int ret;
	char *line;

	fd = open_file(file);
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(rt, line);
		if (ret > 0)
			break ;
		line = get_next_line(fd);
	}
}
void	init_mlx(t_mlx *rt)
{
	rt->element = ft_split("A C L sp pl cy", ' ');
	rt->win_height = 720;
	rt->win_width = 1080;
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_mlx rt;
		int ret;
		init_mlx(&rt);
		ret = parse_scene(argv[1], &rt);


	}
	else
		printf("Wrong number of argument/format! ./minirt <filename>")
}