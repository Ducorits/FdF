/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/19 15:08:16 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42.h"
#include "libft.h"

int	in_window(int x, int y, t_fdf *fdf)
{
	if (x + fdf->x_offset < WINDOW_WIDTH
		&& y + fdf->y_offset < WINDOW_HEIGHT
		&& y + fdf->y_offset > 0
		&& x + fdf->x_offset > 0)
		return (1);
	return (0);
}

void	clear_image(t_fdf *fdf)
{
	unsigned int	i;
	int				*image;

	i = 0;
	image = (int *)fdf->render->pixels;
	while (i < fdf->render->height * fdf->render->width)
	{
		image[i] = 0;
		i++;
	}
}

void	draw_horizontal(t_fdf *fdf, t_3dvec p1, t_3dvec p2)
{
	int	dx;
	int	dy;
	int	y;
	int	x;
	int	d;

	x = p1.x;
	dx = p2.x - p1.x;
	y = p1.y - p1.z;
	dy = (p2.y - p2.z) - (p1.y - p1.z);
	d = (dy << 1) - dx;
	while (x <= p2.x && in_window(x, y, fdf))
	{
		if (in_window(x, y, fdf))
			mlx_put_pixel(fdf->render, x + fdf->x_offset,
				y + fdf->y_offset, 0xffffffff);
		if (d > 0)
		{
			if (p1.y - p1.z < p2.y - p2.z)
				y++;
			else
				y--;
			d = d - (dx << 1);
		}
		d = d + (dy << 1);
		x++;
	}
}

void	draw_vertical(t_fdf *fdf, t_3dvec p1, t_3dvec p2)
{
	int	dx;
	int	dy;
	int	y;
	int	x;
	int	d;

	x = p1.x;
	y = p1.y - p1.z;
	dx = p1.x - p2.x;
	dy = (p2.y - p2.z) - (p1.y - p1.z);
	d = (dx << 1) - dy;
	while (y <= p2.y - p2.z && in_window(x, y, fdf))
	{
		if (in_window(x, y, fdf))
			mlx_put_pixel(fdf->render, x + fdf->x_offset,
				y + fdf->y_offset, 0xffffffff);
		if (d > 0)
		{
			if (p1.x < p2.x)
				x++;
			else
				x--;
			d = d - (dy << 1);
		}
		d = d + (dx << 1);
		y++;
	}
}

void	drawline(t_fdf *fdf, t_3dvec a, t_3dvec b)
{
	int	dx;
	int	dy;

	dx = a.x - b.x;
	dy = (a.y - a.z) - (b.y - b.z);
	if (ft_abs(dx) > ft_abs(dy))
	{
		if (a.x <= b.x)
			draw_horizontal(fdf, a, b);
		else
			draw_horizontal(fdf, b, a);
	}
	else
	{
		if (a.y <= b.y)
			draw_vertical(fdf, a, b);
		else
			draw_vertical(fdf, b, a);
	}
}

void	fdf_frame(void *param)
{
	t_fdf	*fdf;
	int		x;
	int		y;

	y = 0;
	fdf = (t_fdf *)param;
	clear_image(fdf);
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x + 1 < fdf->map_width)
				drawline(fdf, fdf->vecmap[y * fdf->map_width + x],
					fdf->vecmap[y * fdf->map_width + x + 1]);
			if (y + 1 < fdf->map_height)
				drawline(fdf, fdf->vecmap[y * fdf->map_width + x],
					fdf->vecmap[(y + 1) * fdf->map_width + x]);
			x++;
		}
		y++;
	}
}

void	fdf_loop(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &fdf_keyhook, (void *)fdf);
	mlx_loop_hook(fdf->mlx, fdf_frame, (void *)fdf);
	mlx_loop(fdf->mlx);
}
