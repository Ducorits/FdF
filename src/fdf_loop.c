/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/27 14:21:41 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42.h"
#include "libft.h"

static void	prep_lines(int x, int y, t_fdf *fdf)
{
	t_3dvec	a3d;
	t_3dvec	b3d;
	t_point	a;
	t_point	b;

	if (x + 1 < fdf->map_width)
	{
		a3d = get_point(x, y, fdf);
		b3d = get_point(x + 1, y, fdf);
		a = perspective_transform(a3d, fdf);
		b = perspective_transform(b3d, fdf);
		if (in_window(a) || in_window(b))
			drawline(fdf, a, b);
	}
	if (y + 1 < fdf->map_height)
	{
		a3d = get_point(x, y, fdf);
		b3d = get_point(x, y + 1, fdf);
		a = perspective_transform(a3d, fdf);
		b = perspective_transform(b3d, fdf);
		if (in_window(a) || in_window(b))
			drawline(fdf, a, b);
	}
}

static void	update_mouse(t_fdf *fdf)
{
	fdf->last_mouse_x = fdf->mouse_x;
	fdf->last_mouse_y = fdf->mouse_y;
	mlx_get_mouse_pos(fdf->mlx, &fdf->mouse_x, &fdf->mouse_y);
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		fdf->x_offset += fdf->mouse_x - fdf->last_mouse_x;
		fdf->y_offset += fdf->mouse_y - fdf->last_mouse_y;
	}
}

static void	draw_image(t_fdf *fdf)
{
	int		x;
	int		y;

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
		image[i] = 0;
		i++;
	}
}

void	fdf_frame(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	update_mouse(fdf);
	clear_image(fdf);
	draw_image(fdf);
}

void	fdf_loop(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &fdf_keyhook, (void *)fdf);
	mlx_loop_hook(fdf->mlx, fdf_frame, (void *)fdf);
	mlx_scroll_hook(fdf->mlx, fdf_scrollhook, (void *)fdf);
	mlx_loop(fdf->mlx);
}
