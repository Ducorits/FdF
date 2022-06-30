/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 16:03:36 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/30 16:10:49 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	fdf_free(t_fdf *fdf)
{
	free(fdf->map);
	free(fdf->mlx);
	free(fdf);
}
