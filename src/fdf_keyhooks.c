/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_keyhooks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 15:02:05 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/19 14:01:38 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == 1)
		scale_map(fdf, 2);
	if (keydata.key == MLX_KEY_MINUS && keydata.action == 1)
		scale_map(fdf, 0.5);
	if (keydata.key == MLX_KEY_Q && keydata.action == 1)
		rotate_map(fdf, -0.5);
	if (keydata.key == MLX_KEY_E && keydata.action == 1)
		rotate_map(fdf, 0.5);
}
