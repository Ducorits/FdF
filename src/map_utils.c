/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 21:30:22 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/20 22:30:41 by dritsema      ########   odam.nl         */
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

	fdf->x_offset = (WINDOW_WIDTH / 2);
	fdf->y_offset = (WINDOW_HEIGHT / 2);
	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->vecmap[i].x = (i % fdf->map_width) - (fdf->map_width / 2);
		fdf->vecmap[i].y = (i / fdf->map_width) - (fdf->map_height / 2);
		fdf->vecmap[i].z = fdf->map[i];
		i++;
	}
}

// W = 0, S = 1, A = 2, D = 3
void	move_map(t_fdf *fdf, int dir)
{
	if (dir == 0)
		fdf->y_offset += 10;
	else if (dir == 1)
		fdf->y_offset -= 10;
	else if (dir == 2)
		fdf->x_offset += 10;
	else if (dir == 3)
		fdf->x_offset -= 10;
}
