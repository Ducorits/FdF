/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/21 17:59:46 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/21 17:59:55 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
