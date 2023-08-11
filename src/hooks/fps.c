/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sulim <sulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:11:15 by jyim              #+#    #+#             */
/*   Updated: 2023/08/11 21:31:20 by sulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
//remove for evaluation
#include <sys/time.h>

double	time_stamp(void)
{
	struct timeval	current_time;
	double			ms;

	gettimeofday(&current_time, NULL);
	ms = ((double)(current_time.tv_sec) *1000
			+ (double)(current_time.tv_usec) / 1000);
	return (ms);
}

void	framerate(t_mlx *rt)
{
	double	delta_time;
	double	current_time;

	current_time = time_stamp();
	delta_time = current_time - rt->time;
	rt->time = current_time;
}