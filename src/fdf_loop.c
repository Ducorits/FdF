/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/07 19:48:30 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42.h"
#include "libft.h"
#include <math.h>

t_intvec	veci(t_3dvec vecf)
{
	t_intvec	veci;

	veci.x = vecf.x;
	veci.y = vecf.y;
	veci.z = vecf.z;
	return (veci);
}

static void	prep_lines(int x, int y, t_fdf *fdf)
{
	t_3dvec	a;
	t_3dvec	b;
	t_3dvec	pa;
	t_3dvec	pb;

	if (x + 1 < fdf->map_width)
	{
		a = get_point(x, y, fdf);
		b = get_point(x + 1, y, fdf);
		a = transform_point(a, fdf);
		b = transform_point(b, fdf);
		if ((int)a.z + (fdf->z_offset >> 2) > 0
			&& (int)b.z + (fdf->z_offset >> 2) > 0
			&& (int)a.z + (fdf->z_offset >> 2) < fdf->ffar
			&& (int)b.z + (fdf->z_offset >> 2) < fdf->ffar)
		{
			pa = a;
			pb = b;
			a = perspective_transform(a, fdf);
			b = perspective_transform(b, fdf);
			if (in_window(veci(a)))
				drawline(fdf, veci(b), veci(a), pb, pa);
			else if (in_window(veci(b)))
				drawline(fdf, veci(a), veci(b), pa, pb);
		}
	}
	if (y + 1 < fdf->map_height)
	{
		a = get_point(x, y, fdf);
		b = get_point(x, y + 1, fdf);
		a = transform_point(a, fdf);
		b = transform_point(b, fdf);
		if ((int)a.z + (fdf->z_offset >> 2) > 0
			&& (int)b.z + (fdf->z_offset >> 2) > 0
			&& (int)a.z + (fdf->z_offset >> 2) < fdf->ffar
			&& (int)b.z + (fdf->z_offset >> 2) < fdf->ffar)
		{
			pa = a;
			pb = b;
			a = perspective_transform(a, fdf);
			b = perspective_transform(b, fdf);
			if (in_window(veci(a)))
				drawline(fdf, veci(b), veci(a), pb, pa);
			else if (in_window(veci(b)))
				drawline(fdf, veci(a), veci(b), pa, pb);
		}
	}
}

static void	update_mouse(t_fdf *fdf)
{
	fdf->last_mouse_x = fdf->mouse_x;
	fdf->last_mouse_y = fdf->mouse_y;
	mlx_get_mouse_pos(fdf->mlx, &fdf->mouse_x, &fdf->mouse_y);
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		fdf->x_offset += (fdf->mouse_x - fdf->last_mouse_x) * fdf->zoom;
		fdf->y_offset += (fdf->mouse_y - fdf->last_mouse_y) * fdf->zoom;
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
