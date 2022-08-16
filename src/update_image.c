/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_image.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 11:38:27 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/16 12:22:35 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../include/MLX42.h"
#include <stdlib.h>

void	update_image(t_fdf *fdf)
{
	if ((unsigned int)(fdf->mlx->width) != fdf->image->width
		|| (unsigned int)(fdf->mlx->height) != fdf->image->height)
	{
		mlx_delete_image(fdf->mlx, fdf->image);
		free(fdf->depth_buffer);
		fdf->image = mlx_new_image(fdf->mlx, fdf->mlx->width, fdf->mlx->height);
		fdf->depth_buffer = malloc((fdf->image->height * fdf->image->width)
				* sizeof(int));
		if (fdf->image == 0 || fdf->depth_buffer == 0)
			fdf_exit("fdf_init", 8);
		if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
			fdf_exit("fdf_init", 9);
		perspective_update(fdf);
	}
}
