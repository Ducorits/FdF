/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_keycheck.c                                    :+:    :+:             */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 15:02:05 by dritsema      #+#    #+#                 */
/*   Updated: 2023/07/27 14:55:55 by duco          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	render_keycheck(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		render_init(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
	{
		fdf->projection_mode = 0;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
	{
		fdf->projection_mode = 1;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
	{
		fdf->projection_mode = 2;
		isometric_init(fdf);
		update_transformed_map(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_L) && fdf->key_debounce == 0)
	{
		fdf->render_mode = (fdf->render_mode * -fdf->render_mode) + 1;
		fdf->key_debounce = 1;
	}
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_F) && fdf->key_debounce == 0)
	{
		fdf->fps_control = (fdf->fps_control * -fdf->fps_control) + 1;
		fdf->key_debounce = 1;
		update_transformed_map(fdf);
	}
	else if (!mlx_is_key_down(fdf->mlx, MLX_KEY_L) && !mlx_is_key_down(fdf->mlx, MLX_KEY_F))
		fdf->key_debounce = 0;
}

static int	check_rotate_keys(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_E)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_W)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_S)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_A)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		return (1);
	return (0);
}

static void	rotate_key_action(t_fdf *fdf)
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
	update_transformed_map(fdf);
}

static void	setting_keycheck(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1) && fdf->ffov < 150)
	{
		fdf->ffov += 1;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2) && fdf->ffov > 1)
	{
		fdf->ffov -= 1;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
	{
		fdf->ffar += 0.05 * fdf->z_offset;
		render_update(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_4))
	{
		fdf->ffar -= 0.05 * fdf->z_offset;
		render_update(fdf);
	}
}

void	movement_key_action(t_fdf *fdf)
{
	t_point3d	dir;

	dir.x = 0;
	dir.y = 0;
	dir.z = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->camera_pos.z -= 2;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->camera_pos.z += 2;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
	{
		dir.y += 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
	{
		dir.y += -1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
	{
		dir.x += -1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
	{
		dir.x += 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
	{
		dir.z += 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_SHIFT))
	{
		dir.z += -1;
	}
	printf("dirx: %f, diry: %f, dirz: %f.\n", dir.x, dir.y, dir.z);
	dir = rotate_point(fdf, dir);
	printf("rotated dirx: %f, diry: %f, dirz: %f.\n", dir.x, dir.y, dir.z);
	fdf->camera_pos.x += 2 * dir.x;
	fdf->camera_pos.y += 2 * dir.y;
	fdf->camera_pos.z += 2 * dir.z;
	update_transformed_map(fdf);
}

void	fdf_keycheck(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
	{
		fdf_free(fdf);
		fdf_exit("fdf_keyhook", 0);
	}
	render_keycheck(fdf);
	setting_keycheck(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
	{
		fdf->z_scaling -= 0.01;
		update_transformed_map(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
	{
		fdf->z_scaling += 0.01;
		update_transformed_map(fdf);
	}
	if (check_rotate_keys(fdf))
	{
		if (!fdf->fps_control)
			rotate_key_action(fdf);
		else
			movement_key_action(fdf);
	}
}
