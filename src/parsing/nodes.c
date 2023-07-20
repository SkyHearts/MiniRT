/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:33:52 by jyim              #+#    #+#             */
/*   Updated: 2023/07/19 18:33:52 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include "../../inc/scene.h"
#include "../../inc/camera.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

// t_object	*ft_newcam(void *content)
// {
// 	t_object	*head;

// 	head = malloc(sizeof(t_object));
// 	if (!head)
// 		return (0);
// 	head->content = content;
// 	head->next = NULL;
// 	return (head);
// }

t_light	*ft_newlight(char **split)
{
	t_light	*head;
	char **pos;
	char **color;

	head = malloc(sizeof(t_light));
	if (!head)
		return (0);
	pos = ft_split(split[1], ',');
	head->position.x = ft_atof(pos[0]);
	head->position.y = ft_atof(pos[1]);
	head->position.z = ft_atof(pos[2]);
	head->ratio =  ft_atof(split[2]);
	color = ft_split(split[3], ',');
	head->color.x = ft_atof(color[0]);
	head->color.y =  ft_atof(color[1]);
	head->color.z =  ft_atof(color[2]);
	head->next = NULL;
	return (free_darray(pos), free_darray(color), head);
}

void	ft_lightadd_back(t_light **lst, t_light *new)
{
	t_light	*tmp;

	tmp = (*lst);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}