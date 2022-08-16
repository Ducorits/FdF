/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 21:30:22 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/16 11:29:02 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_map(t_fdf *fdf, float scale)
{
	int	i;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->map3d[i].x *= scale;
		fdf->map3d[i].y *= scale;
		fdf->map3d[i].z *= scale;
		i++;
	}
}

// W = 0, S = 1, A = 2, D = 3
void	move_map(t_fdf *fdf, int dir)
{
	int	step;

	step = 10;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_SHIFT))
		step = 20;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_CONTROL))
		step = 5;
	if (dir == 0)
		fdf->y_offset -= step;
	else if (dir == 1)
		fdf->y_offset += step;
	else if (dir == 2)
		fdf->x_offset -= step;
	else if (dir == 3)
		fdf->x_offset += step;
}
