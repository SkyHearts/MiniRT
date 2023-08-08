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

#include "scene.h"
#include <mlx.h>
//#include "../minilibx/mlx.h"
//#include <../minilibx-opengl/mlx.h>
#include "../utils/libft/libft.h"
#include "../utils/libft/ft_printf.h"
#include "object.h"


#define DEFAULT_VAL 10
#define FALSE 0
#define TRUE 1
#define EPS 1e-6

typedef enum s_key
{
	keyPress = 2,
	keyRelease = 3,
	destroyNotify = 17,
}	t_key;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	void		*img;
	void		*addr;
	int			bpp;
	int			size;
	int			line_length;
	int			endian;
	t_scene		scene;
	char 		**element;
	int			mode;
	int			move;
	int			rotated;
	double		time;	//Personal use, deactivate for submitions
}				t_mlx;

//typedef struct timestep
//{
//	long long	time;
//}				ts;

// Parsing
int		parse_scene(char *file, t_mlx *rt);
int		parse_line (t_mlx *rt, char *line);
int		add_ambient(char **split, t_mlx *rt);
int		add_light(char **split, t_mlx *rt);
int		add_camera(char **split, t_mlx *rt);
void	init_cam(t_mlx *rt);

// Parsing light
t_light		*ft_newlight(char **split);
void		ft_lightadd_back(t_light **lst, t_light *new);
t_object	*ft_newobj(char **split);
void		ft_objadd_back(t_object **lst, t_object *new);

//Parsing Utils
int		split_len(char **split);
int		open_file(char *file);
int		ft_strcmp_clist(char *line, char *cmp);
int		ft_strcmp_wlist(char *line, char **cmp);
double	ft_atof(char *num);
int		str_has_aplha(char *str);
void	free_darray(char **array);
int		check_format(char **split);
t_vec3 	get_coordinate(char *split);
t_vec3	get_color(char *split);
t_vec3	get_normal(char *split);
int		check_col_range(t_vec3 col);
int		check_range(double value, int type);
int		isempty(char *str);
char	**isspace_split(const char *str);
double	degtorad(double theta);
t_vec3	get_up(t_vec3 orientation);

//Print scene
void	print_vec(t_vec3 a);
void	print_ambient(t_mlx	rt);
void	print_cam(t_mlx	rt);
void	print_light(t_mlx	rt);
void	print_obj(t_mlx	rt);
void	ft_printscene(t_mlx	rt);
void	printvec_nl(t_vec3 vec);

//Hooks Events
void	hooks_init(t_mlx *rt);

//Print before render
void	print_cam_debug(t_mlx *rt);
void	print_matrix(t_mat44 matrix);
double 	time_stamp(void);
void	framerate(t_mlx *rt);

//hit interaction
int		hit_object(t_ray r, t_object *obj, t_hit_record *rec, int record);
double	hit_sphere(t_object *obj, t_ray r, t_hit_record *rec, int record);
double	hit_plane(t_object *obj, t_ray r, t_hit_record *rec, int record);
double	hit_cylinder(t_object *obj, t_ray r);
double	hit_cylinder2(t_object *obj, t_ray r, t_hit_record *rec, int record);
double	top_cap(t_object *obj, t_ray r);
double	top_cap2(t_object *obj, t_ray r, t_hit_record *rec, int record);
double	btm_cap(t_object *obj, t_ray r);
t_ray	get_ray(double u, double v, t_mlx *rt);

//hit utils
t_vec3	get_intersect(t_ray r, double t);
t_vec3	get_obj_normal2(t_ray r, t_object *object, t_hit_record *rec, t_vec3 poi);

//Render
int		init_img(t_mlx *rt);
void	render(t_mlx *rt);
void	destroy_img(t_mlx *rt);

//free functions
void	free_all(t_mlx *rt);
#endif