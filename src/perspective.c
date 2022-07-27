/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perspective.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 12:22:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/26 18:58:16 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "libft.h"
#include "MLX42.h"
#include <math.h>

t_point	perspective_transform(t_3dvec p, t_fdf *fdf)
{
	t_3dvec	new_p;
	t_point	p2d;

	p.z = p.z * fdf->z_scaling;
	p.z += 10;
	p.x += (float)(fdf->x_offset / 500);
	p.y += (float)(fdf->y_offset / 500);
	multiply_matrix_vec(&p, &new_p, fdf->proj);
	new_p.x += 1.0f;
	new_p.y += 1.0f;
	new_p.x *= .5 * WINDOW_WIDTH;
	new_p.y *= .5 * WINDOW_HEIGHT;
	p2d.x = new_p.x;
	p2d.y = new_p.y;
	return (p2d);
}

void	perspective_init(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->fnear = 0.1;
	fdf->ffar = 1000;
	fdf->ffov = 90;
	fdf->faspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
	fdf->ffov_rad = 1 / tanf(fdf->ffov * .5 / 180 * 3.14159);
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
	fdf->proj.m[0][0] = fdf->faspect_ratio * fdf->ffov_rad;
	fdf->proj.m[1][1] = fdf->ffov_rad;
	fdf->proj.m[2][2] = fdf->ffar / (fdf->ffar - fdf->fnear);
	fdf->proj.m[3][2] = (-fdf->ffar * fdf->fnear) / (fdf->ffar - fdf->fnear);
	fdf->proj.m[2][3] = 1;
	fdf->proj.m[3][3] = 0;
}
