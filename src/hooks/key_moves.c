/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:21:13 by jyim              #+#    #+#             */
/*   Updated: 2023/08/10 19:18:01 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <stdio.h>

// 'A' and 'D' key (0) (2) Move right and left directions
void	move1(int keysym, t_mlx *rt)
{
	t_camera	*cam;
	t_object	*act_obj;

	cam = &(rt->scene.camera);
	act_obj = (rt->scene.active_object);
	if (keysym == 0)
	{
		if (act_obj == NULL && rt->mode == 1)
			cam->position = sub_vec3(cam->position, cam->vars.right);
		else
			act_obj->position = sub_vec3(act_obj->position, act_obj->var.right);
	}
	else if (keysym == 2)
	{
		if (act_obj == NULL && rt->mode == 1)
			cam->position = add_vec3(cam->position, cam->vars.right);
		else
			act_obj->position = add_vec3(act_obj->position, act_obj->var.right);
	}
}

// 'Q' and 'E' key (12) (14) Move up and down directions
void	move2(int keysym, t_mlx *rt)
{
	t_camera	*cam;
	t_object	*act;

	cam = &(rt->scene.camera);
	act = (rt->scene.active_object);
	if (keysym == 12)
	{
		if (act == NULL && rt->mode == 1)
			cam->position = add_vec3(cam->position, cam->vars.up);
		else
			act->position = add_vec3(act->position, act->var.up);
	}
	else if (keysym == 14)
	{
		if (act == NULL && rt->mode == 1)
			cam->position = sub_vec3(cam->position, cam->vars.up);
		else
			act->position = sub_vec3(act->position, act->var.up);
	}
}

// 'W' and 'S' key (1) (13) Move forward and backward directions
void	move3(int keysym, t_mlx *rt)
{
	t_camera	*cam;
	t_object	*act;

	cam = &(rt->scene.camera);
	act = (rt->scene.active_object);
	if (keysym == 13)
	{
		if (act == NULL && rt->mode == 1)
			cam->position = sub_vec3(cam->position, cam->vars.forward);
		else
			act->position = sub_vec3(act->position, act->var.forward);
	}
	else if (keysym == 1)
	{
		if (act == NULL && rt->mode == 1)
			cam->position = add_vec3(cam->position, cam->vars.forward);
		else
			act->position = add_vec3(act->position, act->var.forward);
	}
}

// ←(123) for rotate left
// →(124) for rotate right
void	rotation1(int keysym, t_mlx *rt)
{
	t_vec3	*dir;
	t_vec3	*n;

	dir = &(rt->scene.camera.direction);
	n = &(rt->scene.active_object->normal);
	if (keysym == 123)
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			(*dir) = vec3(dir->x * cos(DEG1) + dir->z * sin(DEG1),
					dir->y, dir->x * -sin(DEG1) + dir->z * cos(DEG1));
		else
			(*n) = vec3((*n).x * cos(DEG5) + (*n).z * sin(DEG5), (*n).y,
					(*n).x * -sin(DEG5) + (*n).z * cos(DEG5));
		rt->rotated = TRUE;
	}
	else if (keysym == 124)
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			(*dir) = vec3(dir->x * cos(-DEG1) + dir->z * sin(-DEG1),
					dir->y, dir->x * -sin(-DEG1) + dir->z * cos(-DEG1));
		else
			(*n) = vec3((*n).x * cos(-DEG5) + (*n).z * sin(-DEG5), (*n).y,
					(*n).x * -sin(-DEG5) + (*n).z * cos(-DEG5));
		rt->rotated = TRUE;
	}
}

// ↑(126) for rotate up
// ↓(125) for rotate down
void	rotation2(int keysym, t_mlx *rt)
{
	t_vec3	*dir;
	t_vec3	*n;

	dir = &(rt->scene.camera.direction);
	n = &(rt->scene.active_object->normal);
	if (keysym == 126)
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			(*dir) = vec3(dir->x, dir->y * cos(DEG1) - dir->z
					* sin(DEG1), dir->y * sin(DEG1) + dir->z * cos(DEG1));
		else
			(*n) = vec3((*n).x, (*n).y * cos(DEG5) - (*n).z * sin(DEG5),
					(*n).y * sin(DEG5) + (*n).z * cos(DEG5));
		rt->rotated = TRUE;
	}
	else if (keysym == 125)
	{
		if (rt->scene.active_object == NULL && rt->mode == 1)
			(*dir) = vec3(dir->x, dir->y * cos(-DEG1) - dir->z
					* sin(-DEG1), dir->y * sin(-DEG1) + dir->z * cos(-DEG1));
		else
			(*n) = vec3((*n).x, (*n).y * cos(-DEG5) - (*n).z * sin(-DEG5),
					(*n).y * sin(-DEG5) + (*n).z * cos(-DEG5));
		rt->rotated = TRUE;
	}
}
