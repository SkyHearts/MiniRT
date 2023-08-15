/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:45:14 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 13:57:01 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include "../../inc/scene.h"
#include "../../inc/camera.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

//print default value of 10 used, diameter must be more than 0
//print default value of 10 used, height must be more than 0
void	add_cone(char **split, t_object **obj)
{
	(*obj)->type = CONE;
	(*obj)->position = get_coordinate(split[1]);
	(*obj)->normal = get_normal(split[2]);
	(*obj)->deg = ft_atof(split[3]);
	(*obj)->height = ft_atof(split[4]);
	(*obj)->color = get_color(split[5]);
	if ((*obj)->deg <= 0)
		(*obj)->deg = 30.0;
	if ((*obj)->deg >= 90)
		(*obj)->deg = 30.0;
	(*obj)->rad = degtorad((*obj)->deg);
	if ((*obj)->height <= 0)
		(*obj)->height = 10.0;
}
