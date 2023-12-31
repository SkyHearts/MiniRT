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
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

void	init_mlx(t_mlx *rt)
{
	rt->element = ft_split("A C L sp pl cy", ' ');
	rt->win_height = 720;
	rt->win_width = 1080;
	rt->scene.camera.filled = 0;
	rt->scene.act_light = NULL;
	rt->scene.light = NULL;
	rt->scene.object = NULL;
	rt->scene.active_object = NULL;
	rt->scene.ambient.filled = 0;
	rt->mode = 0;
	rt->move = FALSE;
	rt->rotated = FALSE;
	rt->time = time_stamp();
	rt->mlx = mlx_init();
	rt->win = mlx_new_window(rt->mlx, rt->win_width, rt->win_height, "minirt");
	init_img(rt);
}

int	main(int argc, char **argv)
{
	t_mlx	rt;
	int		ret;

	if (argc == 2)
	{
		init_mlx(&rt);
		ret = parse_scene(argv[1], &rt);
		if (ret == 1)
		{
			printf("ERROR!\n");
			return (1);
		}
		ft_printscene(rt);
		print_cam_debug(&rt);
		render(&rt);
		hooks_init(&rt);
		mlx_loop(rt.mlx);
	}
	else
		printf("Wrong number of argument/format! ./minirt <filename>");
}
		//to check parse inputs
		//printf("Position(Main): ");
		//printvec_nl(rt.scene.camera.position);
		//printf("Direction(Main): ");
		//printvec_nl(rt.scene.camera.direction);
		//print_cam_debug(&rt);
