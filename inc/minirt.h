/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:20:43 by jyim              #+#    #+#             */
/*   Updated: 2023/07/18 18:20:43 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_scene		scene;
}				t_mlx;
#endif