/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2023/02/28 17:29:13 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_mouse(t_fdf *fdf)
{
	fdf->last_mouse_x = fdf->mouse_x;
	fdf->last_mouse_y = fdf->mouse_y;
	mlx_get_mouse_pos(fdf->mlx, &fdf->mouse_x, &fdf->mouse_y);
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT) && !fdf->fps_control)
	{
		fdf->x_offset -= (fdf->mouse_x - fdf->last_mouse_x) / (fdf->zoom);
		fdf->y_offset += (fdf->mouse_y - fdf->last_mouse_y) / (fdf->zoom);
	}
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT) && fdf->fps_control)
	{
		fdf->rotation = rotate_around_y(fdf->rotation, ((float)(fdf->mouse_x - fdf->last_mouse_x) / (float)200));
		fdf->rotation = rotate_around_x(fdf->rotation, ((float)(fdf->mouse_y - fdf->last_mouse_y) / (float)200));
		update_transformed_map(fdf);
	}
}

static void	draw_image(t_fdf *fdf)
{
	int			x;
	int			y;

	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			prep_lines(x, y, fdf);
			x++;
		}
		y++;
	}
}

void	clear_image(t_fdf *fdf)
{
	unsigned int	i;
	int				*image;

	i = 0;
	image = (int *)fdf->image->pixels;
	while (i < fdf->image->height * fdf->image->width)
	{
		image[i] = 0x77222222;
		fdf->depth_buffer[i] = 0;
		i++;
	}
}

void	fdf_frame(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	update_image(fdf);
	update_mouse(fdf);
	fdf_keycheck(fdf);
	clear_image(fdf);
	draw_image(fdf);
}

void	fdf_loop(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, fdf_frame, (void *)fdf);
	mlx_scroll_hook(fdf->mlx, fdf_scrollhook, (void *)fdf);
	mlx_loop(fdf->mlx);
}
