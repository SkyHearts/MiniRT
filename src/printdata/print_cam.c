/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:42:24 by jyim              #+#    #+#             */
/*   Updated: 2023/08/12 13:43:22 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../inc/minirt.h"
#include <stdio.h>

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
}
	///* Print transformation matrix */
	//printf("Camera to world matrix: \n");
	//print_matrix(rt->scene.camera.camtoworld);
