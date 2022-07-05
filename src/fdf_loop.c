/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/05 19:15:35 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42.h"

void	fdf_frame(void *param)
{
	t_fdf	*fdf;
	int		x;
	int		y;
	int		color;
	int		x_offset;
	int		y_offset;

	y = 0;
	color = 0xffffffff;
	fdf = (t_fdf *)param;
	x_offset = (WINDOW_WIDTH / 2) - ((fdf->map_width / 2) * SCALE);
	y_offset = (WINDOW_HEIGHT / 2) - ((fdf->map_height / 2) * SCALE);
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			mlx_put_pixel(fdf->render, (x * SCALE) + x_offset, (y * SCALE) + y_offset, color);
			x++;
		}
		y++;
	}
}

void	fdf_loop(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, fdf_frame, (void *)fdf);
	mlx_loop(fdf->mlx);
}
