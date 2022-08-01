/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/20 15:53:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/01 17:44:45 by dritsema      ########   odam.nl         */
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

void	drawline(t_fdf *fdf, t_intvec a, t_intvec b)
{
	t_intvec	delta;
	t_intvec	incre;
	t_intvec	cur;
	t_intvec	error;

	draw_setup(a, b, &delta, &incre);
	error.x = (delta.x >= delta.y) + (delta.x >= delta.z);
	error.y = (delta.y >= delta.z) + (delta.y > delta.x);
	error.z = (delta.z > delta.x) + (delta.z > delta.y);
	if (delta.x == 0)
		error.x = -2000000;
	if (delta.y == 0)
		error.y = -2000000;
	if (delta.z == 0)
		error.z = -2000000;
	cur = b;
	while (cur.x != a.x || cur.y != a.y)
	{
		if (in_window(cur))
			((int *)fdf->image->pixels)
			[(cur.y * fdf->image->width + cur.x)] = 0xFF00FFFF;
		if (error.x >= error.y && error.x >= error.z)
		{
			cur.x += incre.x;
			error.x -= ft_max(delta.y, 1) * ft_max(delta.z, 1) * 3;
		}
		if (error.y >= error.x && error.y >= error.z)
		{
			cur.y += incre.y;
			error.y -= ft_max(delta.x, 1) * ft_max(delta.z, 1) * 3;
		}
		if (error.z >= error.x && error.z >= error.y)
		{
			cur.z += incre.z;
			error.z -= ft_max(delta.y, 1) * ft_max(delta.x, 1) * 3;
		}
	}
}
