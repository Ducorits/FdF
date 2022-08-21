/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 16:07:07 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/21 16:01:04 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

float	get_color_height(t_point3d p, t_fdf *fdf)
{
	float	current;
	float	highest;

	highest = fdf->highest_z;
	highest += ft_abs(fdf->lowest_z);
	current = p.z + ft_abs(fdf->lowest_z);
	return (((current / fdf->highest_z) * 255));
}

t_point3d	set_height_color(t_point3d p, t_fdf *fdf)
{
	int	height;

	height = get_color_height(p, fdf);
	p.r = height;
	p.g = 0x77;
	p.b = 0xFF - height;
	p.color = rgb_to_int(p.r, p.g, p.b);
	return (p);
}

t_point3d	get_point_color(t_point3d p, char *str_map)
{
	p.r = (ft_hextoi(str_map) >> 16) & 0xFF;
	p.g = (ft_hextoi(str_map) >> 8) & 0xFF;
	p.b = ft_hextoi(str_map) & 0xFF;
	p.color = rgb_to_int(p.r, p.g, p.b);
	return (p);
}

int	rgb_interpolate(int c1, int c2, int step_count, int step)
{
	t_rgb	rgb1;
	t_rgb	rgb2;
	float	r_delta;
	float	g_delta;
	float	b_delta;

	if (c1 == c2)
		return (c1);
	rgb1.r = ((c1 >> 24) & 0xFF);
	rgb1.g = ((c1 >> 16) & 0xFF);
	rgb1.b = ((c1 >> 8) & 0xFF);
	rgb2.r = ((c2 >> 24) & 0xFF);
	rgb2.g = ((c2 >> 16) & 0xFF);
	rgb2.b = ((c2 >> 8) & 0xFF);
	r_delta = rgb1.r - rgb2.r;
	g_delta = rgb1.g - rgb2.g;
	b_delta = rgb1.b - rgb2.b;
	rgb2.r = rgb2.r + ((r_delta / step_count) * step);
	rgb2.g = rgb2.g + ((g_delta / step_count) * step);
	rgb2.b = rgb2.b + ((b_delta / step_count) * step);
	return (rgb_to_int(rgb2.r, rgb2.g, rgb2.b));
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0x00);
}
