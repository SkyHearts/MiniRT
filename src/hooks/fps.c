/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:11:15 by jyim              #+#    #+#             */
/*   Updated: 2023/08/13 13:25:47 by jyim             ###   ########.fr       */
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
	double	fps;
	char	*time;

	current_time = time_stamp();
	delta_time = current_time - rt->time;
	rt->time = current_time;
	fps = (int)(1000 / delta_time);
	time = ft_itoa(fps);
	mlx_string_put (rt->mlx, rt->win, 10, 10, 0xFFFFFF, time);
	free(time);
}
