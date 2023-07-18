/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:21:05 by jyim              #+#    #+#             */
/*   Updated: 2023/07/05 11:16:30 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CAMERA_H
# define CAMERA_H

# include "vector3.h"

typedef struct s_camvar
{
	t_vec3			position;
	t_vec3			up;
	t_vec3			right;
	t_vec3			forward;
	float			height;
	float			width;
	float			aspect_r;
	float			theta;
	float			fov;
}				t_camvar;

typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_camvar		vars;
	struct s_camera	*next;
	struct s_camera	*previous;	//to allow two keypress events to iterate through the caamera list
}				t_camera;

#endif