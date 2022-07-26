/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_keyhooks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 15:02:05 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/25 17:57:54 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
// TODO
//

void	fdf_keyhook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		fdf_free(fdf);
		fdf_exit("fdf_keyhook", 0);
	}
	if (keydata.key == MLX_KEY_R)
		reset_map(fdf);
	if (keydata.key == MLX_KEY_EQUAL && (keydata.action == 1 || keydata.action == 2))
		fdf->z_scaling += 0.1;
	if (keydata.key == MLX_KEY_MINUS && (keydata.action == 1 || keydata.action == 2))
		fdf->z_scaling -= 0.1;
	if (keydata.key == MLX_KEY_Q
		&& (keydata.action == 1 || keydata.action == 2))
		rotate_map(fdf, -0.05);
	if (keydata.key == MLX_KEY_E
		&& (keydata.action == 1 || keydata.action == 2))
		rotate_map(fdf, 0.05);
	if (keydata.key == MLX_KEY_W)
		move_map(fdf, 0);
	if (keydata.key == MLX_KEY_S)
		move_map(fdf, 1);
	if (keydata.key == MLX_KEY_A)
		move_map(fdf, 2);
	if (keydata.key == MLX_KEY_D)
		move_map(fdf, 3);
}
