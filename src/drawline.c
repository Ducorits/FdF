/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 15:53:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 12:01:56 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static int	incre_select(int val, int a, int b)
{
	if (val)
		return (a);
	return (b);
}

static void	draw_setup(t_drawline *d, t_line l)
{
	d->delta.x = ft_abs(d->p1.x - d->p2.x);
	d->delta.y = ft_abs(d->p1.y - d->p2.y);
	d->incre.x = incre_select(d->p2.x < d->p1.x, 1, -1);
	d->incre.y = incre_select(d->p2.y < d->p1.y, 1, -1);
	d->error.x = d->delta.x << 1;
	d->error.y = d->delta.y << 1;
	d->cur = d->p2;
	d->step = 1;
	d->step_count = d->delta.x + d->delta.y;
	if (d->step_count == 0)
		d->step_size = 1;
	else
		d->step_size = ft_abs(l.a.z - l.b.z) / d->step_count;
}

static void	draw_point(t_drawline d, t_fdf *fdf, t_line l)
{
	if (in_window(d.cur, fdf))
	{
		d.depth = ((fdf->ffar - ((d.step_size * d.step) + d.base_z)));
		if (d.depth > fdf->depth_buffer[d.cur.y * fdf->image->width + d.cur.x])
		{
			d.color = l.b.color | ((int)((float)(d.depth / fdf->ffar) * 255)
					& 0x000000FF);
			mlx_put_pixel(fdf->image, d.cur.x, d.cur.y, d.color);
			fdf->depth_buffer[d.cur.y * fdf->image->width + d.cur.x] = d.depth;
		}
	}
}

static void	draw_loop(t_drawline d, t_fdf *fdf, t_line l)
{
	while ((d.cur.x != d.p1.x || d.cur.y != d.p1.y) && in_window(d.cur, fdf))
	{
		d.depth = ((fdf->ffar - ((d.step_size * d.step) + d.base_z)));
		if (d.depth > fdf->depth_buffer[d.cur.y * fdf->image->width + d.cur.x])
		{
			d.color = rgb_interpolate(l.a.color,
					l.b.color, d.step_count, d.step)
				| ((int)((float)(d.depth / fdf->ffar) * 255) & 0x000000FF);
			mlx_put_pixel(fdf->image, d.cur.x, d.cur.y, d.color);
			fdf->depth_buffer[d.cur.y * fdf->image->width + d.cur.x] = d.depth;
		}
		if (d.error.x >= d.error.y)
		{
			d.cur.x += d.incre.x;
			d.error.x -= d.delta.y << 1;
		}
		else
		{
			d.cur.y += d.incre.y;
			d.error.y -= d.delta.x << 1;
		}
		d.step++;
	}
}

void	drawline(t_fdf *fdf, t_line proj_l,	t_line l)
{
	t_drawline	d;

	d.p1 = veci(proj_l.a);
	d.p2 = veci(proj_l.b);
	draw_setup(&d, l);
	if (fdf->projection_mode == 0)
		d.base_z = l.a.z + fdf->z_offset + fdf->persz_off;
	else
		d.base_z = l.a.z + fdf->z_offset;
	if (fdf->render_mode == 0)
		draw_loop(d, fdf, l);
	draw_point(d, fdf, l);
}
