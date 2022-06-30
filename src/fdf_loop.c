/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/30 16:44:01 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42.h"

void	fdf_frame(void *fdf)
{
	fdf = (t_fdf *)fdf;


}

void	fdf_loop(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, fdf_frame, (void *)fdf);
	mlx_loop(fdf->mlx);
}
