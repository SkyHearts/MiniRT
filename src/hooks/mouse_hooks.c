/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:13:26 by jyim              #+#    #+#             */
/*   Updated: 2023/08/12 17:55:47 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <stdio.h>

static void	shootray(t_mlx *rt, t_ray ray)
{
	t_object		*tmplst;
	t_hit_record	rec;

	tmplst = rt->scene.object;
	rec.t = INFINITY;
	while (tmplst != NULL)
	{
		if (tmplst->type == 0)
			hit_sphere(tmplst, ray, &rec, 1);
		else if (tmplst->type == 1)
			hit_plane(tmplst, ray, &rec, 1);
		else if (tmplst->type == 2)
			hit_cylinder(tmplst, ray, &rec, 1);
		else if (tmplst->type == 3)
			hit_cone(tmplst, ray, &rec, 1);
		tmplst = tmplst->next;
	}
	if (rec.t == INFINITY)
		rt->scene.active_object = NULL;
	else
		rt->scene.active_object = rec.obj;
}
	///* For debug use only */
	//if (rt->scene.active_object != NULL)
	//{	
	//	if (rec.iscap)
	//		printf("Hit cap\n");
	//	printf("Object Index: %d\n", rt->scene.active_object->index);
	//	printf("Object Type: %d\n", rt->scene.active_object->type);
	//	printf("Object Position: ");
	//	printf("Object Hit\n");
	//	printf("rec hit t:%f\n", rec.t);
	//	printf("rec normal t:\n");
	//	printvec_nl(rec.normal);
	//	printvec_nl(rt->scene.active_object->position);
	//	printf("Forward: ");
	//	printvec_nl(rt->scene.active_object->var.forward);
	//	printf("Right: ");
	//	printvec_nl(rt->scene.active_object->var.right);
	//	printf("Up: ");
	//	printvec_nl(rt->scene.active_object->var.up);
	//}

int	mouse_hook(int mousepress, int x, int y, t_mlx *rt)
{
	t_ray	mouseray;
	double	u;
	double	v;

	if (mousepress == 1 && rt->mode == 1)
	{
		u = (double)x / (rt->win_width - 1);
		v = (double)y / (rt->win_height - 1);
		mouseray = get_ray(u, v, rt);
		shootray(rt, mouseray);
	}
	return (0);
}
