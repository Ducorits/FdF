/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/21 17:59:46 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 11:37:14 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	in_window(t_ivec p, t_fdf *fdf)
{
	if (fdf->projection_mode == 0)
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
