/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 21:30:22 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/14 17:23:43 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	rotate_x(t_fdf *fdf, float degrees)
// {
// 	int	i;

// 	i = 0;
// 	while (i < fdf->map_width * fdf->map_height)
// 	{
// 		fdf->map3d[i] = rotate_vecx(fdf->map3d[i], degrees);
// 		i++;
// 	}
// }

// void	rotate_y(t_fdf *fdf, float degrees)
// {
// 	int	i;

// 	i = 0;
// 	while (i < fdf->map_width * fdf->map_height)
// 	{
// 		fdf->map3d[i] = rotate_vecy(fdf->map3d[i], degrees);
// 		i++;
// 	}
// }

// void	rotate_z(t_fdf *fdf, float degrees)
// {
// 	int	i;

// 	i = 0;
// 	while (i < fdf->map_width * fdf->map_height)
// 	{
// 		fdf->map3d[i] = rotate_vecz(fdf->map3d[i], degrees);
// 		i++;
// 	}
// }

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

void	reset_map(t_fdf *fdf)
{
	int	i;

	fdf->x_offset = (WINDOW_WIDTH >> 1);
	fdf->y_offset = (WINDOW_HEIGHT >> 1);
	fdf->z_offset = 100;
	fdf->z_scaling = 0.1;
	fdf->x_rot = 4.7;
	fdf->y_rot = 0;
	fdf->z_rot = 0;
	fdf->scale = 2;
	fdf->zoom = 1;
	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->map3d[i].x = (i % fdf->map_width) - (fdf->map_width >> 1);
		fdf->map3d[i].y = (i / fdf->map_width) - (fdf->map_height >> 1);
		fdf->map3d[i].z = fdf->map[i];
		i++;
	}
	new_perspective_init(fdf);
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
