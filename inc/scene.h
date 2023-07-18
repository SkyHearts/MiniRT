/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:13:12 by jyim              #+#    #+#             */
/*   Updated: 2023/07/18 22:33:38 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "camera.h"


typedef struct s_ambient
{
	float			ratio;
	t_vec3			color;
	float			ratio;
}				t_ambient;

typedef struct s_light
{
	t_vec3			position;
	t_vec3			color;
	float			ratio;
	struct s_light	*next;
}				t_light;

typedef struct s_object
{
	int				type;
	int				index;
	t_vec3			position;
	t_vec3			normal;
	t_vec3			color;
	float			diameter;
	float			height;
	struct s_object	*next;
}				t_object;

typedef struct s_scene
{
	t_ambient	*ambient;			//NULL first, if != NULL when parsing, return error
	t_object	*object;			//a list of objects to be iterated through to calculate closest hit
	t_camera	*camera;			//a list of camera to allow iterating through different views 
	t_light		*light;				//a list of light to be iterate to obtain brightess colour
	t_object	*active_object;		//current active object to be manipulated and selected by shooting rays and selecting closest hit
	t_camera	*active_camera;		//current acrive camera to be manipulated might remove *camera and just use this
}				t_scene;

#endif