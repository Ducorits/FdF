/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_scrollhook.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 00:01:21 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/27 14:47:44 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "MLX42.h"
#include <stdio.h>

void	fdf_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	mlx_get_mouse_pos(fdf->mlx, &fdf->mouse_x, &fdf->mouse_y);
	if (ydelta > 0)
	{
		scale_map(fdf, 1.5);
		// fdf->x_offset += (WINDOW_WIDTH / 2 - fdf->mouse_x);
		// fdf->y_offset += (WINDOW_HEIGHT / 2 - fdf->mouse_y);
	}
	else if (ydelta < 0)
	{
		scale_map(fdf, 0.75);
		// fdf->x_offset += (WINDOW_WIDTH / 2 - fdf->x_offset) / 2;
		// fdf->y_offset += (WINDOW_HEIGHT / 2 - fdf->y_offset) / 2;
	}
	if (xdelta > 0)
		fdf->x_offset += 1;
	else if (xdelta < 0)
		fdf->x_offset -= 1;
}
