/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 15:53:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/20 15:04:51 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <stdio.h>
#include <math.h>

t_point3d	get_point(int x, int y, t_fdf *fdf)
{
	t_point3d	p;

	p = fdf->transformed_map[y * fdf->map_width + x];
	return (p);
}

int	in_window(t_ivec p, t_fdf *fdf)
{
	if (fdf->render_mode == 0)
	{
		if (p.y > 0
			&& p.x > 0
			&& (unsigned int)p.x < fdf->image->width
			&& (unsigned int)p.y < fdf->image->height
			&& p.z > fdf->fnear
			&& p.z < fdf->ffar)
			return (1);
	}
	else
		if (p.y > 0
			&& p.x > 0
			&& (unsigned int)p.x < fdf->image->width
			&& (unsigned int)p.y < fdf->image->height
			&& p.z < fdf->ffar)
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
	int				color;
	int				depth;

	draw_setup(a, b, &delta, &incre);
	error.x = delta.x << 1;
	error.y = delta.y << 1;
	cur = b;
	step = 1;
	step_count = delta.x + delta.y;
	step_size = ft_abs(bf.z - af.z) / step_count;
	if (fdf->render_mode == 0)
		base_z = af.z + fdf->z_offset + fdf->persz_off;
	else
		base_z = af.z + fdf->z_offset;
	while ((cur.x != a.x || cur.y != a.y) && in_window(cur, fdf))
	{
		depth = (float)((fdf->ffar - ((step_size * step) + base_z)));
		if (depth > fdf->depth_buffer[cur.y * fdf->image->width + cur.x])
		{
			color = rgb_interpolate(af.color, bf.color, step_count, step);
			mlx_put_pixel(fdf->image, cur.x, cur.y, color);
			(fdf->image->pixels)
			[((cur.y * fdf->image->width + cur.x) << 2) + 3] = (int)((float)(depth / fdf->ffar) * 255) & 0xFF;
			fdf->depth_buffer[cur.y * fdf->image->width + cur.x] = depth;
		}
		if (error.x >= error.y)
		{
			cur.x += incre.x;
			error.x -= delta.y << 1;
		}
		else
		{
			cur.y += incre.y;
			error.y -= delta.x << 1;
		}
		step++;
	}
}
