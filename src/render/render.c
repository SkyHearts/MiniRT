/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:08 by jyim              #+#    #+#             */
/*   Updated: 2023/07/24 16:07:14 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minirt.h"
#include "../inc/scene.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

unsigned int	RGBtoColor(t_vec3 color)
{
		unsigned int r = (unsigned int)(color.x * 255.0f);
		unsigned int g = (unsigned int)(color.y * 255.0f);
		unsigned int b = (unsigned int)(color.z * 255.0f);

		unsigned int result = (r << 16) | (g << 8) | b;
		return result;
}
void	img_mlx_pixel_put(t_mlx *rt, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && y >= 0 && x < rt->win_width
		&& y < rt->win_height)
	{
		pixel = rt->addr
			+ (y * rt->line_length + x * (rt->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	init_img(t_mlx *rt)
{
	rt->img = mlx_new_image(rt->win, rt->win_width, rt->win_height);
	if (!rt->img)
		//exit_program(MLX_ERROR);
	rt->addr = mlx_get_data_addr(rt->img, &rt->bpp,
			&rt->line_length, &rt->endian);
	if (!rt->addr)
		//exit_program(MLX_ERROR);
	return (0);
}

void	destroy_img(t_mlx *rt)
{
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	mlx_destroy_image(rt->mlx, rt->img);
	rt->addr = NULL;
	rt->img = NULL;
}	

t_vec3 get_up(t_vec3 orientation)
{
	if (orientation.y == 1.0)
		return(vec3(0,0,1));
	return (vec3(0, 1, 0));
}

void	init_cam(t_mlx *rt)
{
	t_camera *camray;
	t_mat44 translation;
	t_mat44 rotation;
	camray = &(rt->scene.camera);
	camray->vars.aspect_r = (double)rt->win_width / (double)rt->win_height;
	camray->vars.forward = normalize(camray->direction);
	camray->vars.right = cross_vec3(get_up(camray->vars.forward), camray->vars.forward);
	camray->vars.up = cross_vec3(camray->vars.right, camray->vars.forward);
	get_translation(camray->position, &translation);
	get_rotation(&camray, &rotation);
	camray->camtoworld = add_mat(translation, rotation);
}

void	render(t_mlx *rt)
{
	int		x;
	int		y;
	double	_x;
	double	_y;

	y = 0;
	init_img(rt);
	
	while (y < rt->win_height)
	{
		x = 0;
		while (x < rt->win_width)
		{
			t_ray camray;
			camray = getray()

			color = 
			img_mlx_pixel_put(t_mlx *rt, _x, _y, color)
			x++;
		}
		y++;
	}
	destroy_img(rt);
}
