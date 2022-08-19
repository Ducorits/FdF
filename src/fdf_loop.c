/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/19 16:40:02 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42.h"
#include "libft.h"
#include <math.h>

int	check_z(t_point3d p, t_fdf *fdf)
{
	if (fdf->render_mode == 0)
	{
		if (fdf->render_mode == 0
			&& (int)p.z + (fdf->z_offset + fdf->persz_off) > 0
			&& (int)p.z + (fdf->z_offset + fdf->persz_off) < fdf->ffar)
			return (1);
		else if ((int)p.z + (fdf->z_offset) > 0
			&& (int)p.z + (fdf->z_offset) < fdf->ffar)
			return (1);
		return (0);
	}
	return (1);
}

t_ivec	veci(t_point3d p)
{
	t_ivec	veci;

	veci.x = p.x;
	veci.y = p.y;
	veci.z = p.z;
	return (veci);
}

static void	prep_lines(int x, int y, t_fdf *fdf)
{
	t_point3d	a;
	t_point3d	b;
	t_point3d	pa;
	t_point3d	pb;

	if (x + 1 < fdf->map_width)
	{
		a = get_point(x, y, fdf);
		b = get_point(x + 1, y, fdf);
		a = transform_point(a, fdf);
		b = transform_point(b, fdf);
		if (check_z(a, fdf) && check_z(b, fdf))
		{
			pa = a;
			pb = b;
			a = projection_transform(a, fdf);
			b = projection_transform(b, fdf);
			if (in_window(veci(a), fdf))
				drawline(fdf, veci(b), veci(a), pb, pa);
			else if (in_window(veci(b), fdf))
				drawline(fdf, veci(a), veci(b), pa, pb);
		}
	}
	if (y + 1 < fdf->map_height)
	{
		a = get_point(x, y, fdf);
		b = get_point(x, y + 1, fdf);
		a = transform_point(a, fdf);
		b = transform_point(b, fdf);
		if (check_z(a, fdf) && check_z(b, fdf))
		{
			pa = a;
			pb = b;
			a = projection_transform(a, fdf);
			b = projection_transform(b, fdf);
			if (in_window(veci(a), fdf))
				drawline(fdf, veci(b), veci(a), pb, pa);
			else if (in_window(veci(b), fdf))
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
		fdf->x_offset -= (fdf->mouse_x - fdf->last_mouse_x);
		fdf->y_offset += (fdf->mouse_y - fdf->last_mouse_y);
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
