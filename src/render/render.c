/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:08 by jyim              #+#    #+#             */
/*   Updated: 2023/08/07 13:15:58 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

unsigned int	RGBtoColor(t_vec3 color)
{
		unsigned int r = (unsigned int)(color.x);
		unsigned int g = (unsigned int)(color.y);
		unsigned int b = (unsigned int)(color.z);

		unsigned int result = (r << 16) | (g << 8) | b;
		return result;
}
void	img_mlx_pixel_put(t_mlx *rt, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && y >= 0 && x < rt->win_width
		&& y < rt->win_height)
	{
		pixel = rt->addr
			+ (y * rt->line_length + x * (rt->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	init_img(t_mlx *rt)
{
	rt->img = mlx_new_image(rt->mlx, rt->win_width, rt->win_height);
	if (!rt->img)
		return (1);
		//exit_program(MLX_ERROR);
	rt->addr = mlx_get_data_addr(rt->img, &rt->bpp,
			&rt->line_length, &rt->endian);
	if (!rt->addr)
		return (1);
		//exit_program(MLX_ERROR);
	return (0);
}

void	destroy_img(t_mlx *rt)
{
	//mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	mlx_destroy_image(rt->mlx, rt->img);
	rt->addr = NULL;
	rt->img = NULL;
}	

t_vec3 get_up(t_vec3 orientation)
{
	if (orientation.y == 1.0)
		return(vec3(0,0,1));
	return (vec3(0, 1, 0));
}

double degtorad(double theta)
{
	double rad;

	rad = theta * (M_PI/180);
	return (rad);
}

void	init_cam(t_mlx *rt)
{
	t_camera *camray;
	//t_mat44 translation;
	//t_mat44 rotation;
	camray = &(rt->scene.camera);
	if(rt->rotated)
	{
		camray->vars.forward = normalize(sub_vec3(vec3(0, 0, 0), camray->direction));
		camray->vars.right = normalize(cross_vec3(get_up(camray->vars.forward), camray->vars.forward));
		camray->vars.up = normalize(cross_vec3(camray->vars.right, camray->direction));
		rt->rotated = FALSE;
	}
	//camray->vars.aspect_r = (double)rt->win_width / (double)rt->win_height;
	//camray->vars.h = tan((degtorad(camray->vars.fov)/2));
	//camray->vars.view_h = 2.0 * camray->vars.h;
	//camray->vars.view_w = camray->vars.aspect_r * camray->vars.view_h;
	camray->vars.horizontal = mul_double_vec3(camray->vars.view_w, camray->vars.right);
	camray->vars.vertical = mul_double_vec3(camray->vars.view_h, camray->vars.up);
	camray->vars.llc = sub_vec3(sub_vec3(sub_vec3(camray->position, div_double_vec3(2.0, camray->vars.horizontal)), div_double_vec3(2.0, camray->vars.vertical)), camray->vars.forward);
	//get_translation(camray->position, &translation);
	//get_rotation(camray, &rotation);
	//camray->camtoworld = add_mat(translation, rotation);
}

void	print_cam_debug(t_mlx *rt)
{
	printf("CAMERA BEFORE RENDER\n");
	printf("Position: ");
	printvec_nl((*rt).scene.camera.position);
	printf("Forward: ");
	printvec_nl(rt->scene.camera.vars.forward);
	printf("Right: ");
	printvec_nl(rt->scene.camera.vars.right);
	printf("Up: ");
	printvec_nl(rt->scene.camera.vars.up);
	printf("Aspect Ratio: %f\n", rt->scene.camera.vars.aspect_r);
	printf("fov: %f\n", rt->scene.camera.vars.fov);
	printf("h: %f\n", rt->scene.camera.vars.h);
	printf("View_h: %f\n", rt->scene.camera.vars.view_h);
	printf("View_w: %f\n", rt->scene.camera.vars.view_w);
	printf("Lower Left Coner: ");
	printvec_nl(rt->scene.camera.vars.llc);
	//printf("Camera to world matrix: \n");
	//print_matrix(rt->scene.camera.camtoworld);
}

t_ray	get_ray(double u, double v, t_mlx *rt)
{
	t_ray ray;

	ray.origin = rt->scene.camera.position;
	ray.direction = normalize(sub_vec3(add_vec3(add_vec3(rt->scene.camera.vars.llc, mul_double_vec3(u, rt->scene.camera.vars.horizontal)),mul_double_vec3(v, rt->scene.camera.vars.vertical)), ray.origin));
	return (ray);
}

int	inlight(t_vec3 poi, t_object *object, t_light *light)
{
	double	light_dis;
	double	intersect_dis;

	light_dis = length(sub_vec3(poi, light->position));
	intersect_dis = length(sub_vec3(poi, object->position));
	if (light_dis < intersect_dis)
		return (1);
	return (0);
}

t_vec3 get_obj_normal(t_ray r, t_object *object, t_light *light)
{
	t_vec3	poi;
	t_vec3	result;
	(void) light;
	double	height;

	result = vec3(0,0,0);
	poi = add_vec3(r.origin, mul_double_vec3(object->t, r.direction));
	if (object->type == 0)
	{
		result = normalize(sub_vec3(poi, object->position));
		if (dot_vec3(r.direction, result) > 0.0)
			result = mul_double_vec3(-1, result);
	}
	if (object->type == 1)
	{
		result = object->normal;
		//if (dot_vec3(r.direction, result) > 0.0)
		//	result = mul_double_vec3(-1, result);
		//if (dot_vec3(sub_vec3(light->position, object->normal), result) > 0.0)
		//	result = mul_double_vec3(-1, result);
	}
	if (object->type == 2)
	{
		height = dot_vec3(normalize(object->normal), sub_vec3(poi, object->position));
		result = normalize(sub_vec3(poi, add_vec3(object->position, mul_double_vec3(height, object->normal))));
		if (dot_vec3(r.direction, result) > 0.0)
			result = mul_double_vec3(-1, result);
	}
	return result;
}

color clamp_vec(color *col, double min, double max)
{
	if (col->color.x < min)
		col->color.x = min;
	else if (col->color.x > max)
		col->color.x = max;
	if (col->color.y < min)
		col->color.y = min;
	else if (col->color.y > max)
		col->color.y = max;
	if (col->color.z < min)
		col->color.z = min;
	else if (col->color.z > max)
		col->color.z = max;
	return (*col);
}
t_vec3	getlightdir(t_ray camray,t_light *light,t_hit_record *rec)
{
	t_vec3	light_direction;
	
	light_direction = normalize(sub_vec3(light->position, add_vec3(camray.origin, mul_double_vec3(rec->t, camray.direction))));
	if (dot_vec3(camray.direction,light_direction) > 0.0)
		light_direction = normalize(mul_double_vec3(-1, light_direction));
	return (light_direction);
}

color ray_color(t_object *object, t_ray camray, t_light *light)
{
	color			pixel_color;
	t_vec3			light_direction;
	//t_vec3			obj_normal;
	t_light			*current_light;
	t_hit_record	rec;
	double			cosine;

	double			specular_strength;
	t_vec3			view_direction;
	t_vec3			reflect_direction;
	double			spec;
	t_vec3			specular;
	color			white_color;

	specular_strength = 0.5;
	pixel_color.color = vec3(0,0,0);
	white_color.color = vec3(255,255,255);
	current_light = light;
	//rec.t = INFINITY;

	if (hit_object(camray, object, &rec) > 0)
	{
		while (current_light != NULL)
		{
			//obj_normal = get_obj_normal(camray, rec.obj, current_light);
			//light_direction = normalize(sub_vec3(current_light->position, add_vec3(camray.origin, mul_double_vec3(rec.t, camray.direction))));
			//light_direction = getlightdir(camray, current_light, &rec);
			light_direction = normalize(sub_vec3(current_light->position, rec.poi));
			cosine = dot_vec3(light_direction, rec.normal);
			view_direction = normalize(sub_vec3(camray.direction, rec.obj->position));
			reflect_direction = reflect(mul_double_vec3(-1, light_direction), mul_double_vec3(1, rec.normal));
			spec = pow(fmax(dot_vec3(view_direction, reflect_direction), 0), 32);
			specular = mul_double_vec3((specular_strength * spec), current_light->color);
			if (cosine < 0)
				break;
			else
				// pixel_color.color = mul_double_vec3(light->ratio, mul_double_vec3(cosine, rec.obj->color));
				pixel_color.color = add_vec3(specular, mul_double_vec3(light->ratio, mul_double_vec3(cosine, rec.obj->color)));
				// pixel_color.color = mul_double_vec3(light->ratio, mul_double_vec3(cosine, rec.obj->color));
				//pixel_color.color = (rec.obj->color);
			current_light = current_light->next;
		}	
	}
	return (clamp_vec(&pixel_color, 0.0, 255.0));
}

void	render(t_mlx *rt)
{
	int			x;
	int			y;
	int			step;
	t_object	*obj;

	if (rt->mode == 1)
		step = 4;
	else
		step = 1;
	y = rt->win_height - 1;
	//init_img(rt);
	ft_memset(rt->addr, 0, ((rt->win_height * rt->line_length) + (rt->win_width * (rt->bpp/8))));
	init_cam(rt);
	//print_cam_debug(rt);
	obj = rt->scene.object;
	while (y >= 0)
	{
		x = 0;
		while (x < rt->win_width)
		{
			t_ray camray;

			double u = (double)x / (rt->win_width - 1);
			double v = (double)y / (rt->win_height - 1);

			camray = get_ray(u, v, rt);
			//write ray data for debug
			color pixel_color = ray_color(obj, camray, rt->scene.light);
			img_mlx_pixel_put(rt, x, y, RGBtoColor(pixel_color.color));
			//img_mlx_pixel_put(rt, x, y, 0xffffff);
			x+= step;
		}
		y -= step;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	//destroy_img(rt);
}
