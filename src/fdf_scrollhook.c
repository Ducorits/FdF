/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_scrollhook.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 00:01:21 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/15 17:41:10 by dritsema      ########   odam.nl         */
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
		fdf->z_offset += 10;
		fdf->zoom *= 1.01;
	}
	else if (ydelta < 0)
	{
		fdf->z_offset -= 10;
		fdf->zoom *= .99;
	}
	if (xdelta > 0)
		fdf->x_offset += 10;
	else if (xdelta < 0)
		fdf->x_offset -= 10;
}
