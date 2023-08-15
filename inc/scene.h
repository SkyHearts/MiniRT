/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:13:12 by jyim              #+#    #+#             */
/*   Updated: 2023/08/15 12:43:34 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "camera.h"

typedef enum s_objtype
{
	SPHERE = 0,
	PLANE = 1,
	CYLINDER = 2,
	CONE = 3,
}	t_objtype;

typedef struct s_color
{
	t_vec3			color;
}	t_color;

typedef struct s_ambient
{
	int				filled;
	double			ratio;
	t_vec3			color;
}				t_ambient;

typedef struct s_light
{
	t_vec3			position;
	t_vec3			color;
	double			ratio;
	struct s_light	*previous;
	struct s_light	*next;
}				t_light;

typedef struct s_vars
{
	t_vec3			up;
	t_vec3			right;
	t_vec3			forward;
}				t_var;

typedef struct s_object
{
	int				type;
	int				index;
	t_vec3			position;
	t_vec3			normal;
	t_vec3			color;
	double			diameter;
	double			radius;
	double			height;
	double			deg;
	double			rad;
	t_var			var;
	double			t;
	struct s_object	*next;
}				t_object;

//ambient, NULL first, if != NULL when parsing, return error
//object, a list of objects to be iterated through to calculate closest hit
//camera, a camera with all variable stored
//light, a list of light to be iterate to obtain brightess colour
//active_object, current active object to be manipulated and selected by
// shooting rays and selecting closest hit
//act_light, iterate through a list of lights to be modified
typedef struct s_scene
{
	t_ambient		ambient;
	t_object		*object;
	t_camera		camera;
	t_light			*light;
	t_object		*active_object;
	t_light			*act_light;
}				t_scene;

#endif