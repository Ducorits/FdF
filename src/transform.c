/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2023/02/28 18:37:06 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	multiply_matrix_vec(t_point3d *i, t_point3d *o, t_mat4x4 m)
{
	float	w;

	o->x = i->x * m.m[0][0] + i->y * m.m[1][0] + i->z * m.m[2][0] + m.m[3][0];
	o->y = i->x * m.m[0][1] + i->y * m.m[1][1] + i->z * m.m[2][1] + m.m[3][1];
	o->z = i->x * m.m[0][2] + i->y * m.m[1][2] + i->z * m.m[2][2] + m.m[3][2];
	w = i->x * m.m[0][3] + i->y * m.m[1][3] + i->z * m.m[2][3] + m.m[3][3];
	if (w != 1)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}

static t_point3d	transform_point(t_point3d p, t_fdf *fdf)
{
	if (!fdf->fps_control)
	{
		p.x -= (fdf->map_width / 2);
		p.y -= (fdf->map_height / 2);
	}
	// p.z = p.z * fdf->z_scaling;
	// p.x *= 2;
	// p.y *= 2;
	if (fdf->fps_control)
	{
		p.x -= (fdf->map_width / 2);
		p.y -= (fdf->map_height / 2);
		p.x -= fdf->camera_pos.x;
		p.y -= fdf->camera_pos.y;
		p.z -= fdf->camera_pos.z;
	}
	p = rotate_point(fdf, p);
	return (p);
}

void	update_transformed_map(t_fdf *fdf)
{
	int	i;

	printf("camx: %f, camy: %f, camz: %f.\n", fdf->camera_pos.x, fdf->camera_pos.y, fdf->camera_pos.z);
	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->transformed_map[i] = transform_point(fdf->map3d[i], fdf);
		i++;
	}
}
