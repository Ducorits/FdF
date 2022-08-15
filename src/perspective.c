/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perspective.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 12:22:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/15 20:24:46 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "libft.h"
#include "MLX42.h"
#include <math.h>

t_mat3x3	set_mat3x3_0(t_mat3x3 m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			m.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (m);
}

t_mat4x4	set_mat4x4_0(t_mat4x4 m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (m);
}

t_point3d	perspective_transform(t_point3d p, t_fdf *fdf)
{
	t_point3d	new_p;

	p.z += fdf->z_offset >> 2;
	p.x -= (fdf->x_offset >> 4);
	p.y -= (fdf->y_offset >> 4);
	multiply_matrix_vec(&p, &new_p, fdf->proj);
	new_p.x *= WINDOW_WIDTH >> 2;
	new_p.y *= WINDOW_HEIGHT >> 2;
	new_p.x += WINDOW_WIDTH >> 1;
	new_p.y += WINDOW_HEIGHT >> 1;
	return (new_p);
}

void	perspective_update(t_fdf *fdf)
{
	float	r;
	float	l;
	float	t;
	float	b;
	float	scale;

	scale = tanf(fdf->ffov * .5 / 180 * 3.14159265359) * fdf->fnear;
	r = fdf->faspect_ratio * scale;
	l = -r;
	t = scale;
	b = -t;
	fdf->proj.m[0][0] = 2 * fdf->fnear / (r - l);
	fdf->proj.m[1][1] = 2 * fdf->fnear / (t - b);
	fdf->proj.m[2][0] = (r + l) / (r - l);
	fdf->proj.m[2][1] = (t + b) / (t - b);
	fdf->proj.m[2][2] = -(fdf->ffar + fdf->fnear) / (fdf->ffar - fdf->fnear);
	fdf->proj.m[2][3] = -1;
	fdf->proj.m[3][2] = -2 * fdf->ffar * fdf->fnear / (fdf->ffar - fdf->fnear);
}

void	perspective_init(t_fdf *fdf)
{
	fdf->x_offset = 0;
	fdf->y_offset = 100;
	fdf->fnear = 0.1;
	fdf->ffar = 500;
	fdf->ffov = 60;
	fdf->faspect_ratio = WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	fdf->proj = set_mat4x4_0(fdf->proj);
	perspective_update(fdf);
}
