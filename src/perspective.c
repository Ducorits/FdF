/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perspective.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 12:22:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/02 02:22:32 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "libft.h"
#include "MLX42.h"
#include <math.h>

t_3dvec	perspective_transform(t_3dvec p, t_fdf *fdf)
{
	t_3dvec	new_p;

	p.z += 100;
	p.z += fdf->z_offset >> 2;
	p.x += (fdf->x_offset >> 2);
	p.y += (fdf->y_offset >> 2);
	multiply_matrix_vec(&p, &new_p, fdf->proj);
	// new_p.x += 1.0f;
	// new_p.y += 1.0f;
	// new_p.z += 1.0f;
	new_p.x *= 1000;
	new_p.y *= 1000;
	new_p.z *= 1000;
	new_p.x += WINDOW_WIDTH >> 1;
	new_p.y += WINDOW_HEIGHT >> 1;
	// new_p.z -= 500;
	return (new_p);
}

void	perspective_update(t_fdf *fdf)
{
	fdf->ffov_rad = 1 / tanf(fdf->ffov * .5 / 180 * 3.14159);
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
