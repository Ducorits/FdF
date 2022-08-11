/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perspective.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 12:22:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/11 15:04:13 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "libft.h"
#include "MLX42.h"
#include <math.h>

// t_point3d	perspective_transform(t_point3d p, t_fdf *fdf)
// {
// 	t_point3d	new_p;

// 	p.z += 100;
// 	p.z += fdf->z_offset >> 2;
// 	p.x += (fdf->x_offset >> 2);
// 	p.y += (fdf->y_offset >> 2);
// 	multiply_matrix_vec(&p, &new_p, fdf->proj);
// 	// new_p.x += 1.0f;
// 	// new_p.y += 1.0f;
// 	new_p.z = (new_p.z + 1.0f) * .5;
// 	new_p.x *= 1000;
// 	new_p.y *= 1000;
// 	new_p.z *= 100;
// 	// new_p.z += 0.4;
// 	new_p.x += WINDOW_WIDTH >> 1;
// 	new_p.y += WINDOW_HEIGHT >> 1;
// 	// new_p.z += 500;
// 	return (new_p);
// }

void	perspective_update(t_fdf *fdf)
{
	fdf->ffov_rad = 1 / tanf(fdf->ffov * .5 / 180 * 3.14159265359);
	fdf->proj.m[0][0] = fdf->faspect_ratio * fdf->ffov_rad;
	fdf->proj.m[1][1] = fdf->ffov_rad;
	fdf->proj.m[2][2] = fdf->ffar / (fdf->ffar - fdf->fnear);
	fdf->proj.m[3][2] = (-fdf->ffar * fdf->fnear) / (fdf->ffar - fdf->fnear);
	fdf->proj.m[2][3] = 1;
	fdf->proj.m[3][3] = 0;
}

void	perspective_init(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->x_offset = 0;
	fdf->y_offset = 0;
	fdf->fnear = 0.4;
	fdf->ffar = 1000;
	fdf->ffov = 90;
	fdf->faspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			fdf->proj.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	perspective_update(fdf);
}

t_point3d	perspective_transform(t_point3d p, t_fdf *fdf)
{
	t_point3d	new_p;

	p.z += fdf->z_offset >> 2;
	p.x -= (fdf->x_offset >> 4);
	p.y -= (fdf->y_offset >> 4);
	multiply_matrix_vec(&p, &new_p, fdf->proj);
	// new_p.x += 1.0f;
	// new_p.y += 1.0f;
	// new_p.z = (new_p.z + 1.0f) * .5;
	new_p.x *= WINDOW_WIDTH >> 2;
	new_p.y *= WINDOW_HEIGHT >> 2;
	// new_p.z -= fdf->fnear;
	// new_p.z *= fdf->ffar;
	new_p.x += WINDOW_WIDTH >> 1;
	new_p.y += WINDOW_HEIGHT >> 1;
	// new_p.z += 500;
	return (new_p);
}

void	new_perspective_update(t_fdf *fdf)
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
	fdf->proj.m[0][1] = 0;
	fdf->proj.m[0][2] = 0;
	fdf->proj.m[0][3] = 0;

	fdf->proj.m[1][0] = 0;
	fdf->proj.m[1][1] = 2 * fdf->fnear / (t - b);
	fdf->proj.m[1][2] = 0;
	fdf->proj.m[1][3] = 0;

	fdf->proj.m[2][0] = (r + l) / (r - l);
	fdf->proj.m[2][1] = (t + b) / (t - b);
	fdf->proj.m[2][2] = -(fdf->ffar + fdf->fnear) / (fdf->ffar - fdf->fnear);
	fdf->proj.m[2][3] = -1;

	fdf->proj.m[3][0] = 0;
	fdf->proj.m[3][1] = 0;
	fdf->proj.m[3][2] = -2 * fdf->ffar * fdf->fnear / (fdf->ffar - fdf->fnear);
	fdf->proj.m[3][3] = 0;
}

void	new_perspective_init(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->x_offset = 0;
	fdf->y_offset = 100;
	fdf->fnear = 0.1;
	fdf->ffar = 500;
	fdf->ffov = 60;
	fdf->faspect_ratio = WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			fdf->proj.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			fdf->rotation.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	fdf->rotation.m[0][0] = 1;
	fdf->rotation.m[1][1] = 1;
	fdf->rotation.m[2][2] = 1;
	new_perspective_update(fdf);
}
