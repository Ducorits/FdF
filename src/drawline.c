/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 15:53:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/28 13:46:53 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"

t_3dvec	get_point(int x, int y, t_fdf *fdf)
{
	t_3dvec	p;

	p.x = fdf->vecmap[y * fdf->map_width + x].x;
	p.y = fdf->vecmap[y * fdf->map_width + x].y;
	p.z = fdf->vecmap[y * fdf->map_width + x].z;
	return (p);
}

int	in_window(t_point p)
{
	if (p.x < WINDOW_WIDTH
		&& p.y < WINDOW_HEIGHT
		&& p.y > 0
		&& p.x > 0)
		return (1);
	return (0);
}

static int	incre_select(int val, int a, int b)
{
	if (val)
		return (a);
	return (b);
}

static void	draw_setup(t_point a, t_point b, t_point *delta, t_point *incre)
{
	delta->x = ft_abs(a.x - b.x);
	delta->y = ft_abs(a.y - b.y);
	incre->x = incre_select(b.x < a.x, 1, -1);
	incre->y = incre_select(b.y < a.y, 1, -1);
}

void	drawline(t_fdf *fdf, t_point a, t_point b)
{
	t_point	delta;
	t_point	incre;
	t_point	cur;
	int		error;

	draw_setup(a, b, &delta, &incre);
	error = ((delta.y - delta.x) << 1);
	cur = b;
	while (cur.x != a.x || cur.y != a.y)
	{
		if (in_window(cur))
			((int *)fdf->image->pixels)
			[(cur.y * fdf->image->width + cur.x)] = 0xFF00FFFF;
		if (error >= 0)
		{
			cur.y += incre.y;
			error -= delta.x << 1;
		}
		if (error < 0)
		{
			cur.x += incre.x;
			error += delta.y << 1;
		}
	}
}
