/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orthographic.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 13:57:00 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/19 13:41:52 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "libft.h"
#include "MLX42.h"
#include <math.h>

t_point3d	orthographic_transform(t_point3d p, t_fdf *fdf)
{
	t_point3d	new_p;

	p.z += fdf->z_offset;
	p.x -= (fdf->x_offset >> 4);
	p.y -= (fdf->y_offset >> 4);
	multiply_matrix_vec(&p, &new_p, fdf->orth);
	new_p.x += fdf->image->width >> 1;
	new_p.y += fdf->image->height >> 1;
	return (new_p);
}

void	orthographic_update(t_fdf *fdf)
{
	fdf->orth.m[0][0] = fdf->fnear * fdf->faspect_ratio / (fdf->scale);
	fdf->orth.m[1][1] = -fdf->fnear * fdf->faspect_ratio / (fdf->scale);
	fdf->orth.m[2][2] = 1;
	fdf->orth.m[3][3] = 1;
}

void	orthographic_init(t_fdf *fdf)
{
	fdf->rotation = rotate_around_x(fdf->rotation, 2.4);
	fdf->orth = set_mat4x4_0(fdf->orth);
	orthographic_update(fdf);
}
