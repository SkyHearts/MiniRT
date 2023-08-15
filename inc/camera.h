/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:21:05 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 12:46:09 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector3.h"

	//t_vec3			position;

typedef struct s_camvar
{
	t_vec3			up;
	t_vec3			right;
	t_vec3			forward;
	double			aspect_r;
	double			theta;
	double			fov;
	double			h;
	double			view_w;
	double			view_h;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			llc;
}				t_camvar;
//lower left coner

typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	t_camvar		vars;
	t_mat44			camtoworld;
	int				filled;
}				t_camera;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}				t_ray;

//matrix
void	set_zero(t_mat44 *matrix);
void	set_identity(t_mat44 *matrix);
void	get_translation(t_vec3 position, t_mat44 *translation);
void	get_rotation(t_camera *camray, t_mat44 *rotation);
t_mat44	add_mat(t_mat44 matrix_a, t_mat44 matrix_b);
t_mat44	worldtocam(t_mat44 camtoworld);

#endif