/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 15:53:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/02 14:37:35 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <stdio.h>
#include <math.h>

t_3dvec	get_point(int x, int y, t_fdf *fdf)
{
	t_3dvec	p;

	p.x = fdf->vecmap[y * fdf->map_width + x].x;
	p.y = fdf->vecmap[y * fdf->map_width + x].y;
	p.z = fdf->vecmap[y * fdf->map_width + x].z;
	return (p);
}

int	in_window(t_intvec p)
{
	if (p.x < WINDOW_WIDTH
		&& p.y < WINDOW_HEIGHT
		&& p.y > 0
		&& p.x > 0
		&& p.z > 0
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

static void	draw_setup(t_intvec a, t_intvec b, t_intvec *delta, t_intvec *incre)
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

// static int	get_step_count(t_intvec delta)
// {

// }

void	drawline(t_fdf *fdf, t_intvec a, t_intvec b, t_3dvec af, t_3dvec bf)
{
	t_intvec	delta;
	t_intvec	incre;
	t_intvec	cur;
	t_intvec	error;
	float		step;
	float		step_count;
	int			color;

	draw_setup(a, b, &delta, &incre);
	// error.x = (delta.x >= delta.y) + (delta.x >= delta.z);
	// error.y = (delta.y >= delta.z) + (delta.y > delta.x);
	// error.z = (delta.z > delta.x) + (delta.z > delta.y);
	// if (delta.x == 0)
	error.x = delta.x << 1;
	// if (delta.y == 0)
	error.y = delta.y << 1;
	// if (delta.z == 0)
	// 	error.z = -2000000;
	cur = b;
	step = 1;
	step_count = delta.x + delta.y;
	while ((cur.x != a.x || cur.y != a.y) && in_window(cur))
	{
		// if (delta.z != 0)
		// 	printf("delta.z: %i\n", delta.z);
		// printf("delta.z: %i, step: %f, step_count: %f, color: %i\n", delta.z, step, step_count, color);
		if (in_window(cur))
		{
			color = (float)(1 / (((bf.z - af.z / step_count) * step) + af.z) * 255);
			color = (float)((af.z / 100) * 255);
			// color = step / step_count * 255;
			// color = (float)(af.z * 255);
			(fdf->image->pixels)
			[((cur.y * fdf->image->width + cur.x) << 2)] = color;
			(fdf->image->pixels)
			[((cur.y * fdf->image->width + cur.x) << 2) + 1] = color;
			(fdf->image->pixels)
			[((cur.y * fdf->image->width + cur.x) << 2) + 2] = color;
			(fdf->image->pixels)
			[((cur.y * fdf->image->width + cur.x) << 2) + 3] = 0xFF;
			// ((int *)fdf->image->pixels)
			// [(cur.y * fdf->image->width + cur.x)] = 0xFFFFFFFF;
		}
		if (error.x >= error.y)
		{
			cur.x += incre.x;
			error.x -= delta.y << 1;
			step++;
			// error.x -= ft_max(delta.y, 1) * ft_max(delta.z, 1) * 3;
		}
		else
		{
			cur.y += incre.y;
			error.y -= delta.x << 1;
			step++;
			// error.y -= ft_max(delta.x, 1) * ft_max(delta.z, 1) * 3;
		}
		// if (error.z >= error.x && error.z >= error.y)
		// {
		// 	cur.z += incre.z;
		// 	// error.z -= ft_max(delta.y, 1) * ft_max(delta.x, 1) * 3;
		// }
	}
}
