/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_keycheck.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 15:02:05 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/28 14:59:17 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
// TODO
//

void	fdf_keycheck(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
	{
		fdf_free(fdf);
		fdf_exit("fdf_keyhook", 0);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		reset_map(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->z_scaling += 0.01;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->z_scaling -= 0.01;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		rotate_map(fdf, -0.05);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		rotate_map(fdf, 0.05);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		move_map(fdf, 0);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		move_map(fdf, 1);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		move_map(fdf, 2);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		move_map(fdf, 3);
}
