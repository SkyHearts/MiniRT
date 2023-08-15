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

# include "scene.h"
# include <mlx.h>
# include "scene.h"
# include <mlx.h>
//#include "../minilibx/mlx.h"
//#include <../minilibx-opengl/mlx.h>
# include "../utils/libft/libft.h"
# include "../utils/libft/ft_printf.h"
# include "object.h"
# define DEFAULT_VAL 10
# define FALSE 0
# define TRUE 1
# define EPS 1e-7
//# define EPS 0.001
# define DEG1 0.0174533
# define DEG5 0.0872665
# define MLX_ERROR "MLX ERROR"
# define SPECULAR_STRENGTH 0.5

typedef struct s_counter
{
	int	x;
	int	y;
	int	step;
}	t_counter;

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
	char		**element;
	int			mode;
	int			move;
	int			rotated;
	double		time;
}				t_mlx;
//Time variable Personal use, deactivate for submitions

//typedef struct timestep
//{
//	long long	time;
//}				ts;

// Parsing
int				parse_scene(char *file, t_mlx *rt);
int				parse_line(t_mlx *rt, char *line);
int				add_ambient(char **split, t_mlx *rt);
int				add_light(char **split, t_mlx *rt);
int				add_camera(char **split, t_mlx *rt);
void			init_cam(t_mlx *rt);
t_light			*ft_newlight(char **split);
void			ft_lightadd_back(t_light **lst, t_light *new);

// Parsing obj
int				add_obj(char **split, t_mlx *rt);
t_object		*ft_newobj(char **split);
void			ft_objadd_back(t_object **lst, t_object *new);
void			add_sphere(char **split, t_object **obj);
void			add_plane(char **split, t_object **obj);
void			add_cylinder(char **split, t_object **obj);
void			add_cone(char **split, t_object **obj);

//Parsing Utils
int				split_len(char **split);
int				open_file(char *file);
int				ft_strcmp_clist(char *line, char *cmp);
int				ft_strcmp_wlist(char *line, char **cmp);
double			ft_atof(char *num);
int				str_has_aplha(char *str);
void			free_darray(char **array);
int				check_format(char **split);
t_vec3			get_coordinate(char *split);
t_vec3			get_color(char *split);
t_vec3			get_normal(char *split);
int				check_col_range(t_vec3 col);
int				check_range(double value, int type);
int				check_ext(char *file);
int				check_format(char **split);
int				isempty(char *str);
char			**isspace_split(const char *str);
double			degtorad(double theta);
t_vec3			get_up(t_vec3 orientation);
void			check_type_and_input(char **split, t_object **obj);
void			init_objvar(t_object **obj);
void			reinit_objvar(t_object *obj);

//Print scene
void			print_vec(t_vec3 a);
void			print_ambient(t_mlx	rt);
void			print_cam(t_mlx	rt);
void			print_light(t_mlx	rt);
void			print_sphere(t_object *obj);
void			print_plane(t_object *obj);
void			print_cylinder(t_object *obj);
void			print_obj(t_mlx	rt);
void			ft_printscene(t_mlx	rt);
void			print_cam_debug(t_mlx *rt);
void			print_cone(t_object *obj);

//Hooks Events
void			hooks_init(t_mlx *rt);
int				mouse_hook(int mousepress, int x, int y, t_mlx *rt);
int				press_key(int keysym, t_mlx *rt);
void			move1(int keysym, t_mlx *rt);
void			move2(int keysym, t_mlx *rt);
void			move3(int keysym, t_mlx *rt);
void			rotation1(int keysym, t_mlx *rt);
void			rotation2(int keysym, t_mlx *rt);
void			light_move(int keysym, t_mlx *rt);
void			iterate_light(int keysym, t_mlx *rt);

//Print before render
void			print_cam_debug(t_mlx *rt);
void			print_matrix(t_mat44 matrix);
double			time_stamp(void);
void			framerate(t_mlx *rt);

//hit interaction
int				hit_object(t_ray r, t_object *obj, t_hit_record *rec, int \
record);
double			hit_sphere(t_object *obj, t_ray r, t_hit_record *rec, int \
record);
double			hit_plane(t_object *obj, t_ray r, t_hit_record *rec, int \
record);
//double		hit_cylinder(t_object *obj, t_ray r);
double			hit_cylinder(t_object *obj, t_ray r, t_hit_record *rec, int \
record);
void			assign_cylinder(t_cylinder2 *cy, t_object *obj, t_ray r);
double			top_cap(t_object *obj, t_ray r);
double			top_cap2(t_object *obj, t_ray r, t_hit_record *rec, int record);
double			btm_cap(t_object *obj, t_ray r);
double			btm_cap2(t_object *obj, t_ray r, t_hit_record *rec, int record);
double			apex(t_object *obj, t_ray r, t_hit_record *rec, t_cone *cn);
double			cone_cap(t_object *obj, t_ray r, t_hit_record *rec, int record);
double			hit_cone(t_object *obj, t_ray r, t_hit_record *rec, int record);
void			update_rec(t_object *obj, t_ray r, t_hit_record *rec, int \
record);
void			update_rec2(t_object *obj, t_ray r, t_hit_record *rec, int \
record);
void			update_rec3(t_object *obj, t_ray r, t_hit_record *rec, int \
record);
void			update_rec4(t_object *obj, t_ray r, t_hit_record *rec, int \
record);
t_vec3			get_cone_normal(t_ray r, t_object *obj, t_hit_record *rec, \
t_vec3 poi);
t_ray			get_ray(double u, double v, t_mlx *rt);

// color
t_color			ray_color(t_scene *sc, t_ray camray);
t_vec3			get_shadow_origin(t_hit_record *rec);
t_color			clamp_vec(t_color *col, t_vec3 min, double max);
unsigned int	rgb2color(t_vec3 color);

//hit utils
t_vec3			get_intersect(t_ray r, double t);
t_vec3			get_obj_normal2(t_ray r, t_object *object, t_hit_record *rec, \
t_vec3 poi);

//Render
int				init_img(t_mlx *rt);
void			render(t_mlx *rt);
void			destroy_img(t_mlx *rt);
void			img_mlx_pixel_put(t_mlx *rt, int x, int y, int color);

//free functions
void			free_all(t_mlx *rt);
#endif