/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/21 01:10:39 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42.h"
#include "libft.h"

void	clear_image(t_fdf *fdf)
{
	unsigned int	i;
	int				*image;

	i = 0;
	image = (int *)fdf->render->pixels;
	while (i < fdf->render->height * fdf->render->width)
	{
		image[i] = 0;
		i++;
	}
}

void	fdf_frame(void *param)
{
	t_fdf	*fdf;
	int		x;
	int		y;
	t_point	a;
	t_point	b;

	y = 0;
	fdf = (t_fdf *)param;
	clear_image(fdf);
	fdf->last_mouse_x = fdf->mouse_x;
	fdf->last_mouse_y = fdf->mouse_y;
	mlx_get_mouse_pos(fdf->mlx, &fdf->mouse_x, &fdf->mouse_y);
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		fdf->x_offset += fdf->mouse_x - fdf->last_mouse_x;
		fdf->y_offset += fdf->mouse_y - fdf->last_mouse_y;
	}
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x + 1 < fdf->map_width)
			{
				a.x = fdf->vecmap[y * fdf->map_width + x].x + fdf->x_offset;
				a.y = fdf->vecmap[y * fdf->map_width + x].y + fdf->y_offset - (fdf->vecmap[y * fdf->map_width + x].z * fdf->z_scaling);
				b.x = fdf->vecmap[y * fdf->map_width + x + 1].x + fdf->x_offset;
				b.y = fdf->vecmap[y * fdf->map_width + x + 1].y + fdf->y_offset - (fdf->vecmap[y * fdf->map_width + x + 1].z * fdf->z_scaling);
				drawline(fdf, a, b);
			}
			if (y + 1 < fdf->map_height)
			{
				a.x = fdf->vecmap[y * fdf->map_width + x].x + fdf->x_offset;
				a.y = fdf->vecmap[y * fdf->map_width + x].y + fdf->y_offset - (fdf->vecmap[y * fdf->map_width + x].z * fdf->z_scaling);
				b.x = fdf->vecmap[(y + 1) * fdf->map_width + x].x + fdf->x_offset;
				b.y = fdf->vecmap[(y + 1) * fdf->map_width + x].y + fdf->y_offset - (fdf->vecmap[(y + 1) * fdf->map_width + x].z * fdf->z_scaling);
				drawline(fdf, a, b);
			}
			x++;
		}
		y++;
	}
}

void	fdf_loop(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &fdf_keyhook, (void *)fdf);
	mlx_loop_hook(fdf->mlx, fdf_frame, (void *)fdf);
	mlx_scroll_hook(fdf->mlx, fdf_scrollhook, (void *)fdf);
	mlx_loop(fdf->mlx);
}
