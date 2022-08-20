/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_scrollhook.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 00:01:21 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/20 14:15:34 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "MLX42.h"
#include <stdio.h>

void	fdf_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (ydelta > 0)
	{
		if (fdf->render_mode == 0)
			fdf->persz_off += 5;
		else
			fdf->zoom *= 1.01;
	}
	else if (ydelta < 0)
	{
		if (fdf->render_mode == 0)
			fdf->persz_off -= 5;
		else
			fdf->zoom *= 0.99;
	}
	(void)xdelta;
}
