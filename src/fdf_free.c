/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 16:03:36 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/11 14:41:56 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "libft.h"

void	fdf_free(t_fdf *fdf)
{
	if (fdf->map)
		free(fdf->map);
	if (fdf->depth_buffer)
		free(fdf->depth_buffer);
	if (fdf->map3d)
		free(fdf->map3d);
	if (fdf->image)
		mlx_delete_image(fdf->mlx, fdf->image);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	// if (fdf)
	// 	free(fdf);
}
