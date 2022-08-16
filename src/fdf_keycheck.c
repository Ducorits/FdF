/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_keycheck.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 15:02:05 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/16 16:26:26 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>

static void	render_keycheck(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		render_init(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
	{
		fdf->render_mode = 0;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
	{
		fdf->render_mode = 1;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		fdf->render_mode = 2;
		render_update(fdf);
	}
}

static void	rotate_keycheck(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->rotation = rotate_around_z(fdf->rotation, -0.05);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->rotation = rotate_around_z(fdf->rotation, 0.05);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->rotation = rotate_around_x(fdf->rotation, -0.05);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->rotation = rotate_around_x(fdf->rotation, 0.05);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->rotation = rotate_around_y(fdf->rotation, -0.05);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->rotation = rotate_around_y(fdf->rotation, 0.05);
}

void	fdf_keycheck(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
	{
		fdf_free(fdf);
		fdf_exit("fdf_keyhook", 0);
	}
	render_keycheck(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
	{
		fdf->ffov += 1;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
	{
		fdf->ffov -= 1;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->z_scaling -= 0.01;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->z_scaling += 0.01;
	rotate_keycheck(fdf);
}
