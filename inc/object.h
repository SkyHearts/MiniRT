/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:37:39 by jyim              #+#    #+#             */
/*   Updated: 2023/08/03 14:26:52 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef struct s_sphere
{
	double	a;
	double	b;
	double	c;
	double	t;
	double  discriminant;
}				t_sphere;

typedef struct s_cylinder
{
	double	a;
	double	b;
	double	c;
	double	t;
	double  discriminant;
}				t_cylinder;
#endif