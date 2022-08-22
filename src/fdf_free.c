/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 16:03:36 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 11:59:43 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	fdf_free(t_fdf *fdf)
{
	free(fdf->map);
	free(fdf->depth_buffer);
	free(fdf->map3d);
	free(fdf->transformed_map);
	if (fdf->image)
		mlx_delete_image(fdf->mlx, fdf->image);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
}
