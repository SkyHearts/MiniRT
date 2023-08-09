/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:14:19 by jyim              #+#    #+#             */
/*   Updated: 2023/08/09 13:40:54 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>


// Release key: Exit, and edit/raytrace mdoe
// Esc key (53) Free and exit
// '1' key (18) switch between edit mode and raytracing mode
//'~'  key deselect by setting active object as NULL
int	rel_key(int keysym, t_mlx *rt)
{
	if (keysym == 53)
	{
		free_all(rt);
		exit(0);
	}
	else if (keysym == 18)
	{
		if (rt->mode == 0)
			return (printf("Edit mode\n"), rt->mode = 1, 0);
		else
			return (printf("Phong mode\n"), rt->mode = 0, 0);
	}
	else if (keysym == 50)
	{
		if (rt->scene.active_object != NULL)
			return (rt->scene.active_object = NULL, printf("Deselected\n"), 0);
	}
	return (0);
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
// Axis abit weird, positive y is down, positve x is right.
// Y must be reversed to get desired outcome
int	press_key(int keysym, t_mlx *rt)
{
	if (rt->mode == 1)
	{
		move1(keysym, rt);
		move2(keysym, rt);
		rotation1(keysym, rt);
		rotation2(keysym, rt);
		rt->move = TRUE;
	}
	return (0);
}

int	close_mlx(t_mlx *rt)
{
	free_all(rt);
	exit(0);
}

int	frame_refresh(t_mlx *rt)
{
	if (rt->move == TRUE)
	{
		render(rt);
		//framerate(rt);
		rt->move = FALSE;
	}
	else
	//{
		render(rt);
	//	//framerate(rt);
	//}
	return (0);
}

void	hooks_init(t_mlx *rt)
{
	mlx_key_hook(rt->win, &rel_key, rt);
	mlx_hook(rt->win, keyPress, 0, &press_key, rt);
	mlx_hook(rt->win, destroyNotify, 0, &close_mlx, rt);
	mlx_mouse_hook(rt->win, &mouse_hook, rt);
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