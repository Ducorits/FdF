/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perspective.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 12:22:24 by dritsema      #+#    #+#                 */
/*   Updated: 2023/02/28 17:34:21 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point3d	perspective_transform(t_point3d p, t_fdf *fdf)
{
	t_point3d	new_p;

	p.z += fdf->persz_off;
	multiply_matrix_vec(&p, &new_p, fdf->pers);
	new_p.x *= fdf->image->width / 4;
	new_p.y *= fdf->image->height / 4;
	new_p.x += fdf->image->width / 2;
	new_p.y += fdf->image->height / 2;
	return (new_p);
}

void	perspective_update(t_fdf *fdf)
{
	float	r;
	float	l;
	float	t;
	float	b;

	r = fdf->faspect_ratio * fdf->scale;
	l = -r;
	t = fdf->scale;
	b = -t;
	fdf->pers.m[0][0] = -2 * fdf->fnear / (r - l);
	fdf->pers.m[1][1] = 2 * fdf->fnear / (t - b);
	fdf->pers.m[2][0] = (r + l) / (r - l);
	fdf->pers.m[2][1] = (t + b) / (t - b);
	fdf->pers.m[2][2] = -(fdf->ffar + fdf->fnear) / (fdf->ffar - fdf->fnear);
	fdf->pers.m[2][3] = -1;
	fdf->pers.m[3][2] = -2 * fdf->ffar * fdf->fnear / (fdf->ffar - fdf->fnear);
}

void	perspective_init(t_fdf *fdf)
{
	fdf->rotation = rotate_around_x(fdf->rotation, -4.7);
	perspective_update(fdf);
}
