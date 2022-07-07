/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 16:03:36 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/07 16:32:41 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "libft.h"

void	fdf_free(t_fdf *fdf)
{
	if (fdf->map)
		free(fdf->map);
	if (fdf->vecmap)
		free(fdf->vecmap);
	if (fdf->render)
		mlx_delete_image(fdf->mlx, fdf->render);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	if (fdf)
		free(fdf);
}