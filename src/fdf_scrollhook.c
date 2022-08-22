/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_scrollhook.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 00:01:21 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 14:09:36 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (ydelta > 0)
	{
		if (fdf->projection_mode == 0)
			fdf->persz_off += 5;
		else
			fdf->zoom *= 1.01;
	}
	else if (ydelta < 0)
	{
		if (fdf->projection_mode == 0)
			fdf->persz_off -= 5;
		else
			fdf->zoom *= 0.99;
	}
	if (xdelta > 0)
	{
		if (fdf->projection_mode == 0)
			fdf->persz_off += 15;
		else
			fdf->zoom *= 1.025;
	}
	else if (xdelta < 0)
	{
		if (fdf->projection_mode == 0)
			fdf->persz_off -= 15;
		else
			fdf->zoom *= 0.975;
	}
}
