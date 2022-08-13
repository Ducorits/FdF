/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 15:53:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/14 00:13:59 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <stdio.h>
#include <math.h>

int	get_color(t_point3d a, t_point3d b, int step_count, int step)
{
	int	r_delta;
	int	g_delta;
	int	b_delta;
	int	color;

	r_delta = ft_abs(b.r - a.r);
	g_delta = ft_abs(b.g - a.g);
	b_delta = ft_abs(b.b - a.b);
	color = a.
	color = (((r_delta / step_count) * step) & 0xFF) << 16;
	color = color | (((g_delta / step_count) * step) & 0xFF) << 8;
	color = color | (((b_delta / step_count) * step) & 0xFF);
	return (color);
}

t_point3d	get_point(int x, int y, t_fdf *fdf)
{
	t_point3d	p;

	// p.x = fdf->map3d[y * fdf->map_width + x].x;
	// p.y = fdf->map3d[y * fdf->map_width + x].y;
	// p.z = fdf->map3d[y * fdf->map_width + x].z;
	p = fdf->map3d[y * fdf->map_width + x];
	return (p);
}

int	in_window(t_ivec p)
{
	if (p.x < WINDOW_WIDTH
		&& p.y < WINDOW_HEIGHT
		&& p.y > 0
		&& p.x > 0
		&& p.z > 0.1
		&& p.z < 1000)
		return (1);
	return (0);
}

static int	incre_select(int val, int a, int b)
{
	if (val)
		return (a);
	return (b);
}

static void	draw_setup(t_ivec a, t_ivec b, t_ivec *delta, t_ivec *incre)
{
	delta->x = ft_abs(a.x - b.x);
	delta->y = ft_abs(a.y - b.y);
	delta->z = ft_abs(a.z - b.z);
	incre->x = incre_select(b.x < a.x, 1, -1);
	incre->y = incre_select(b.y < a.y, 1, -1);
	incre->z = incre_select(b.z < a.z, 1, -1);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

// static int	get_step_count(t_ivec delta)
// {

// }

void	drawline(t_fdf *fdf, t_ivec a, t_ivec b, t_point3d af, t_point3d bf)
{
	t_ivec			delta;
	t_ivec			incre;
	t_ivec			cur;
	t_ivec			error;
	float			step;
	float			step_size;
	float			step_count;
	float			base_z;
	// int				color;
	int				depth;
	// unsigned int	pixel;

	draw_setup(a, b, &delta, &incre);
	error.x = delta.x << 1;
	error.y = delta.y << 1;
	cur = b;
	step = 1;
	step_count = delta.x + delta.y;
	step_size = ft_abs(bf.z - af.z) / step_count;
	base_z = af.z + (fdf->z_offset >> 2);
	while ((cur.x != a.x || cur.y != a.y) && in_window(cur))
	{
		if (in_window(cur))
		{
			depth = (float)((fdf->ffar - ((step_size * step) + base_z)) / fdf->ffar) * 255;
			// color = fdf->far - (step_size * step);
			// color = (float)(((fdf->ffar - (af.z + (fdf->z_offset >> 2))) / fdf->ffar) * 255);
			// color = step / step_count * 255;
			// color = (float)(af.z * 255);
			if (depth >= fdf->depth_buffer[cur.y * fdf->image->width + cur.x])
			{
				// color = get_color(af, bf, step_count, step);
				// pixel = ((int *)fdf->image->pixels)
				// [(cur.y * fdf->image->width + cur.x)];
				// pixel = pixel | (0xFF000000 & af.color);
				// pixel = pixel | (0x00FF0000 & af.color);
				// pixel = pixel | (0x0000FF00 & af.color);
				// pixel = af.color;
				// mlx_put_pixel(fdf->image, cur.x, cur.y, af.color);
				(fdf->image->pixels)
				[((cur.y * fdf->image->width + cur.x) << 2)] = af.color & 0xFF;
				(fdf->image->pixels)
				[((cur.y * fdf->image->width + cur.x) << 2) + 1] = (af.color >> 8) & 0xFF;
				(fdf->image->pixels)
				[((cur.y * fdf->image->width + cur.x) << 2) + 2] = (af.color >> 16) & 0xFF;
				(fdf->image->pixels)
				[((cur.y * fdf->image->width + cur.x) << 2) + 3] = depth & 0xFF;
				// pixel = (0x000000FF & depth);
				fdf->depth_buffer[cur.y * fdf->image->width + cur.x] = depth;
			}
		}
		if (error.x >= error.y)
		{
			cur.x += incre.x;
			error.x -= delta.y << 1;
			step++;
		}
		else
		{
			cur.y += incre.y;
			error.y -= delta.x << 1;
			step++;
		}
	}
}
