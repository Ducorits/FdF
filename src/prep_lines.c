/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prep_lines.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/21 17:26:59 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/21 19:34:37 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_z(t_point3d p, t_fdf *fdf)
{
	if (fdf->projection_mode == 0)
	{
		if ((int)p.z + (fdf->z_offset + fdf->persz_off) > fdf->fnear
			&& (int)p.z + (fdf->z_offset + fdf->persz_off) < fdf->ffar)
			return (1);
	}
	else if ((int)p.z + (fdf->z_offset) > 0
		&& (int)p.z + (fdf->z_offset) < fdf->ffar)
		return (1);
	return (0);
}

t_ivec	veci(t_point3d p)
{
	t_ivec	veci;

	veci.x = p.x;
	veci.y = p.y;
	veci.z = p.z;
	return (veci);
}

static void	prep_line(t_line l, t_fdf *fdf)
{
	t_line	proj_l;
	t_line	sproj_l;
	t_line	s_l;

	if (check_z(l.a, fdf) && check_z(l.b, fdf))
	{
		proj_l.a = projection_transform(l.a, fdf);
		proj_l.b = projection_transform(l.b, fdf);
		if (in_window(veci(proj_l.a), fdf))
		{
			s_l.a = l.b;
			s_l.b = l.a;
			sproj_l.a = proj_l.b;
			sproj_l.b = proj_l.a;
			drawline(fdf, sproj_l, s_l);
		}
		else if (in_window(veci(proj_l.b), fdf))
			drawline(fdf, proj_l, l);
	}
}

void	prep_lines(int x, int y, t_fdf *fdf)
{
	t_line	l;

	if (x + 1 < fdf->map_width)
	{
		l.a = get_point(x, y, fdf);
		l.b = get_point(x + 1, y, fdf);
		prep_line(l, fdf);
	}
	if (y + 1 < fdf->map_height)
	{
		l.a = get_point(x, y, fdf);
		l.b = get_point(x, y + 1, fdf);
		prep_line(l, fdf);
	}
	if (x == fdf->map_width - 1 && y == fdf->map_height - 1)
	{
		l.a = get_point(x, y, fdf);
		l.b = l.a;
		prep_line(l, fdf);
	}
}
