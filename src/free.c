/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:36:32 by jyim              #+#    #+#             */
/*   Updated: 2023/07/27 16:15:52 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

void	free_objlst(t_object *obj)
{
	t_object	*tmp_obj;

	tmp_obj = NULL;
	while (obj != NULL)
	{
		tmp_obj = obj;
		obj = obj->next;
		free(tmp_obj);
	}
}

void	free_lightlst(t_light *light)
{
	t_light	*tmp_light;

	tmp_light = NULL;
	while (light != NULL)
	{
		tmp_light = light;
		light = light->next;
		free(tmp_light);
	}
}

void	free_all(t_mlx *rt)
{
	free_objlst(rt->scene.object);
	free_lightlst(rt->scene.light);
}
