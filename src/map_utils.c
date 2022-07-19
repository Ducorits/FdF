/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 21:30:22 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/09 15:14:39 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_map(t_fdf *fdf, float degrees)
{
	int	i;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->vecmap[i] = rotate_vec(fdf->vecmap[i], degrees);
		i++;
	}
}

void	scale_map(t_fdf *fdf, float scale)
{
	int	i;

	i = 0;
	fdf->x_offset -= scale * (fdf->map_width / 2);
	fdf->y_offset -= scale * (fdf->map_height / 2);
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->vecmap[i].x *= scale;
		fdf->vecmap[i].y *= scale;
		fdf->vecmap[i].z *= scale;
		i++;
	}
}

void	reset_map(t_fdf *fdf)
{
	int	i;

	fdf->x_offset = (WINDOW_WIDTH / 2) - ((fdf->map_width / 2) * SCALE);
	fdf->y_offset = (WINDOW_HEIGHT / 2) - ((fdf->map_height / 2) * SCALE);
	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->vecmap[i].x = i % fdf->map_width;
		fdf->vecmap[i].y = i / fdf->map_width;
		fdf->vecmap[i].z = fdf->map[i];
		i++;
	}
}
