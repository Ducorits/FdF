/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 20:29:46 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/16 20:40:37 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_point3d	projection_transform(t_point3d p, t_fdf *fdf)
{
	if (fdf->render_mode == 0)
		p = perspective_transform(p, fdf);
	else if (fdf->render_mode == 1)
		p = orthographic_transform(p, fdf);
	else if (fdf->render_mode == 2)
		p = orthographic_transform(p, fdf);
	return (p);
}

void	get_height_extremes(t_fdf *fdf)
{
	int		i;

	i = 0;
	fdf->highest_z = 0;
	fdf->lowest_z = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		if (fdf->map[i] > fdf->highest_z)
			fdf->highest_z = fdf->map[i];
		if (fdf->map[i] < fdf->lowest_z)
			fdf->lowest_z = fdf->map[i];
		i++;
	}
}

void	render_update(t_fdf *fdf)
{
	if (fdf->render_mode == 0)
		perspective_update(fdf);
	else if (fdf->render_mode == 1)
		orthographic_update(fdf);
	else if (fdf->render_mode == 2)
		orthographic_update(fdf);
}

void	render_init(t_fdf *fdf)
{
	fdf->faspect_ratio = fdf->image->width / (float)(fdf->image->height);
	fdf->z_scaling = 0.1;
	fdf->ffar = 500;
	fdf->fnear = 0.2;
	fdf->rotation = set_mat3x3_0(fdf->rotation);
	fdf->rotation.m[0][0] = 1;
	fdf->rotation.m[1][1] = 1;
	fdf->rotation.m[2][2] = 1;
	fdf->scale = tanf(fdf->ffov * .5 / 180 * 3.14159265359) * fdf->fnear;
	fdf->zoom = 10000 / (fdf->map_height);
	if (fdf->render_mode == 0)
		perspective_init(fdf);
	else if (fdf->render_mode == 1)
		orthographic_init(fdf);
	else if (fdf->render_mode == 2)
		isometric_init(fdf);
	render_update(fdf);
}
