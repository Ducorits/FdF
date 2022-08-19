/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_scrollhook.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 00:01:21 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/19 13:34:12 by dritsema      ########   odam.nl         */
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
		fdf->persz_off += 10;
	}
	else if (ydelta < 0)
	{
		fdf->persz_off -= 10;
	}
	(void)xdelta;
}
