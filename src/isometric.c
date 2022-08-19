/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   isometric.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 15:34:11 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/19 13:53:36 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_init(t_fdf *fdf)
{
	fdf->rotation = set_mat3x3_0(fdf->rotation);
	fdf->rotation.m[0][0] = 1;
	fdf->rotation.m[1][1] = 1;
	fdf->rotation.m[2][2] = 1;
	fdf->rotation = rotate_around_x(fdf->rotation, 2.45);
	fdf->rotation = rotate_around_y(fdf->rotation, 0.6);
	fdf->rotation = rotate_around_z(fdf->rotation, -0.6);
	fdf->x_offset = 0;
	fdf->y_offset = 0;
	fdf->ffov = 80;
	fdf->orth = set_mat4x4_0(fdf->orth);
	render_update(fdf);
}
