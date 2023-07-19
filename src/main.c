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
#include "../inc/minirt.h"
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

float ft_atof(char *num)
{
	int		sign;
	float	whole;
	float	decimal;
	char	*tmp;

	tmp = num;
	sign = 1;
	if (tmp[0] == '-')
	{
		sign *= -1;
		tmp++;
	}
	whole = atoi(tmp);
	while (*tmp != '.' && *tmp)
		tmp++;
	decimal = atoi(++tmp);
	while (decimal > 1)
		decimal /= 10;
	return (sign * (whole + decimal));
}

int str_has_aplha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void free_darray(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

/* 
Check each element for correct number of arugment/parameter
if incorrect number, return 1
Check if each parameter has alphabets
if alphabet exit, return 1
 */
int	check_format(char **split)
{
	int	len;
	int	i;

	i = 0;
	len = split_len(split);
	if (!strcmp(split[0], "A"))
	// print error then return 1, Wrong number of element for A
		if (len != 3)
			return (1);
	else if (!strcmp(split[0], "cy"))
	// print error then return 1, Wrong number of element for cy
		if (len != 6)
			return (1);
	else if (len != 4)
	// print error then return 1, Wrong number of element for split[0]
		return (1);
	while (split[i])
	{
		if (str_has_aplha(split[i]))
		// print error then return 1, Element split[0] has alphabet in parameter
			return (1);
		i++;
	}
	return (0);
}

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
	char	**color;

	s = rt->scene;
	
	if (check_format(split))
		return (1);		// print error then return 1, element format wrong @goto int	check_format(char **split)

	return (0);
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
		ret = add_camera(split, rt);
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
	return (ret);
}
void	init_mlx(t_mlx *rt)
{
	rt->element = ft_split("A C L sp pl cy", ' ');
	rt->win_height = 720;
	rt->win_width = 1080;
	rt->scene.camera = NULL;
	rt->scene.active_camera = NULL;
	rt->scene.light = NULL;
	rt->scene.object = NULL;
	rt->scene.active_object = NULL;
	rt->scene.ambient.filled = 0;
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
		printf("Wrong number of argument/format! ./minirt <filename>");
}
