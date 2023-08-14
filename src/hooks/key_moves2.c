/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_moves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:17:47 by jyim              #+#    #+#             */
/*   Updated: 2023/08/11 21:23:20 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <stdio.h>

// I(34) for forward movement
// K(40) for backwards movement
// U(32) for downwards movement
// O(31) for upwards movement
// J(38) for left movement
// L(37) for right movement
void	light_move(int keysym, t_mlx *rt)
{
	t_light	*light;

	light = rt->scene.act_light;
	if (keysym == 34)
		light->position = sub_vec3(light->position, vec3(0, 0, 1));
	else if (keysym == 40)
		light->position = add_vec3(light->position, vec3(0, 0, 1));
	else if (keysym == 32)
		light->position = add_vec3(light->position, vec3(0, 1, 0));
	else if (keysym == 31)
		light->position = sub_vec3(light->position, vec3(0, 1, 0));
	else if (keysym == 38)
		light->position = sub_vec3(light->position, vec3(1, 0, 0));
	else if (keysym == 37)
		light->position = add_vec3(light->position, vec3(1, 0, 0));
}

void	iterate_light(int keysym, t_mlx *rt)
{
	if (keysym == 43)
	{
		if (rt->scene.act_light->previous != NULL)
			rt->scene.act_light = rt->scene.act_light->previous;
		if (rt->scene.act_light->previous == NULL)
			printf("Reach the first light\n");
	}
	else if (keysym == 47)
	{
		if (rt->scene.act_light->next != NULL)
			rt->scene.act_light = rt->scene.act_light->next;
		if (rt->scene.act_light->next == NULL)
			printf("Reach the last light\n");
	}
}
