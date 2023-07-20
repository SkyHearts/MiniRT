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
#include "../utils/libft/libft.h"
#include "../utils/libft/ft_printf.h"

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_scene		scene;
	char 		**element;
}				t_mlx;

// Parsing
int		parse_line (t_mlx *rt, char *line);
int		add_ambient(char **split, t_mlx *rt);
int		add_light(char **split, t_mlx *rt);
int		add_camera(char **split, t_mlx *rt);

// Parsing light
t_light		*ft_newlight(char **split);
void		ft_lightadd_back(t_light **lst, t_light *new);

//Parsing Utils
int		split_len(char **split);
int		open_file(char *file);
int		ft_strcmp_clist(char *line, char *cmp);
int		ft_strcmp_wlist(char *line, char **cmp);
float	ft_atof(char *num);
int		str_has_aplha(char *str);
void	free_darray(char **array);
int		check_format(char **split);

#endif