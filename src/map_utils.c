/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 21:30:22 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/07 22:29:51 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_map(t_fdf *fdf, float scale)
{
	int	i;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->vecmap[i].x *= scale;
		fdf->vecmap[i].y *= scale;
		fdf->vecmap[i].z *= scale;
		i++;
	}
}

void	reset_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->vecmap[i].x = i % fdf->map_width;
		fdf->vecmap[i].y = i / fdf->map_width;
		fdf->vecmap[i].z = fdf->map[i];
		i++;
	}
}
