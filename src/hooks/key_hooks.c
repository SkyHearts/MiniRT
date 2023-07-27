/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:14:19 by jyim              #+#    #+#             */
/*   Updated: 2023/07/27 15:27:41 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h> //remove for evaluation

// Release key: Exit, and edit/raytrace mdoe
int	rel_key(int keysym, t_mlx *rt)
{
	if (keysym == 53)	//escape key, free and exit program
    {
		//free data function insert here
		free_all(rt);
		//system("leaks -q minirt");
		exit(0);
	}
	else if (keysym == 18)	//'1' switch between edit mode and raytracing mode
	{
		if (rt->mode == 0)
		{
			printf("Edit mode\n");
			rt->mode = 1;
		}
		else
		{
			printf("Raytrace mode\n");
			rt->mode = 0;
		}
	}
	else if (keysym == 150)	//'~'  key deselect by setting active object as NULL
		rt->scene.active_object = NULL;
	return (0);
}
void movement(int keysym, t_mlx *rt)
{
	t_vec3 *dir;

	dir = &(rt->scene.camera.direction);
	if (keysym == 0) //'A'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.position = sub_vec3(rt->scene.camera.position, rt->scene.camera.vars.right);
	}
	else if (keysym == 2) //'D'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.position = add_vec3(rt->scene.camera.position, rt->scene.camera.vars.right);
	}
	else if (keysym == 12) //'Q'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.position = add_vec3(rt->scene.camera.position, rt->scene.camera.vars.up);
	}
	else if (keysym == 14) //'E'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.position = sub_vec3(rt->scene.camera.position, rt->scene.camera.vars.up);
	}
	else if (keysym == 13) //'W'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.position = sub_vec3(rt->scene.camera.position, rt->scene.camera.vars.forward);
	}
	else if (keysym == 1) //'S'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.position = add_vec3(rt->scene.camera.position, rt->scene.camera.vars.forward);
	}
	else if (keysym == 123) //'left'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.direction = vec3(dir->x * cos(0.0174533) + dir->z * sin(0.0174533), dir->y, dir->x * -sin(0.0174533) + dir->z * cos(0.0174533));
	}
	else if (keysym == 124) //'right'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.direction = vec3(dir->x * cos(-0.0174533) + dir->z * sin(-0.0174533), dir->y, dir->x * -sin(-0.0174533) + dir->z * cos(-0.0174533));
	}
		else if (keysym == 126) //'up'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.direction = vec3(dir->x, dir->y * cos(0.0174533) - dir->z * sin(0.0174533), dir->y * sin(0.0174533) + dir->z * cos(0.0174533));
	}
	else if (keysym == 125) //'down'
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			rt->scene.camera.direction = vec3(dir->x, dir->y * cos(-0.0174533) - dir->z * sin(-0.0174533), dir->y * sin(-0.0174533) + dir->z * cos(-0.0174533));
	}
}
// Press key: Camera and object movement
// W(13) for forward movement
// S(1) for backwards movement
// Q(12) for downwards movement
// E(14) for upwards movement
// A(0) for left movement
// D(2) for right movement
// ←(123) for rotate left
// →(124) for rotate right
// ↑(126) for rotate up
// ↓(125) for rotate down
// Axis abit weird, positive y is down, positve x is right. Y must be reversed to get desired outcome
int	press_key(int keysym, t_mlx *rt)
{
	if (rt->mode == 1)
	{
		movement(keysym, rt);
		//rotation(keysym, rt);
		rt->move = TRUE;
	}
	return (0);
}

int close_mlx(t_mlx *rt)
{
    //(void)param;
	//free data function insert here
	free_all(rt);
    exit(0);
}

double time_stamp(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	double ms =
		((double)(current_time.tv_sec) * 1000 +
		(double)(current_time.tv_usec) / 1000);
    return (ms);
}

void	framerate(t_mlx *rt)
{
	double	delta_time;
	double	current_time;
	int		fps;

	current_time = time_stamp();
	delta_time = current_time - rt->time;
	//printf("delta time:%f\n",delta_time);
	rt->time = current_time;
	fps = (int)(1000 / delta_time);
	//printf("%d\n", fps);
	char *time = ft_itoa(fps);
	mlx_string_put (rt->mlx, rt->win, 10, 10, 0xFFFFFF, time);
	free(time);
}

int	frame_refresh(t_mlx *rt)
{
	if (rt->move == TRUE)
	{
		render(rt);
		framerate(rt);
		rt->move = FALSE;
	}
	else
	{
		render(rt);
		framerate(rt);
	}
	return (0);
}

void	hooks_init(t_mlx *rt)
{
	mlx_key_hook(rt->win, &rel_key, rt); //Default for key release
	mlx_hook(rt->win, keyPress, 0, &press_key, rt);
	mlx_hook(rt->win, destroyNotify, 0, &close_mlx, rt);
	mlx_loop_hook(rt->mlx, &frame_refresh, rt);
}


//Rx(a)=
//[1 0 0 ]
//[0 cos(a) -sin(a)]
//[0 sin(a) cos(a) ]

//Ry(b)=
//[cos(b) 0 sin(b)]
//[0 1 0 ]
//[-sin(b) 0 cos(b)]

//Rz(c)=
//[cos(c) -sin(c) 0]
//[sin(c) cos(c) 0]
//[0 0 1]