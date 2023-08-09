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

t_object	*ft_newobj(char **split)
{
	t_object	*head;

	head = malloc(sizeof(t_object));
	if (!head)
		return (0);
	head->index = 1;
	check_type_and_input(split, &head);
	init_objvar(&head);
	head->next = NULL;
	return (head);
}

void	ft_objadd_back(t_object **lst, t_object *new)
{
	t_object	*tmp;
	int			i;

	i = 1;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = (*lst);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tmp->next = new;
	new->index += i;
}

t_light	*ft_newlight(char **split)
{
	t_light	*head;

	head = malloc(sizeof(t_light));
	if (!head)
		return (0);
	head->position = get_coordinate(split[1]);
	head->ratio = ft_atof(split[2]);
	head->color = get_color(split[3]);
	head->next = NULL;
	return (head);
}

void	ft_lightadd_back(t_light **lst, t_light *new)
{
	t_light	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = (*lst);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
