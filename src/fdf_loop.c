/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 15:56:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/07 22:55:17 by dritsema      ########   odam.nl         */
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

void	drawline(t_fdf *fdf, t_3dvec a, t_3dvec b)
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	p;
	int	end;

	dx = (a.x - b.x);
	dy = (a.y - b.y);
	p = 2 * dy - dx;
	if (a.x > b.x)
	{
		x = b.x;
		y = b.y;
		end = a.x;
	}
	else
	{
		x = a.x;
		y = a.y;
		end = b.x;
	}
	mlx_put_pixel(fdf->render, x, y, 0xffffffff);
	while (x < end)
	{
		x = x + 1;
		if (p < 0)
		{
			p = p + 2 * dy;
		}
		else
		{
			y = y + 1;
			p = p + 2 * (dy - dx);
		}
		mlx_put_pixel(fdf->render, x, y, 0xffffffff);
	}
}

/*
plotLine(x0, y0, x1, y1)
	dx = abs(x1 - x0)
	sx = x0 < x1 ? 1 : -1
	dy = -abs(y1 - y0)
	sy = y0 < y1 ? 1 : -1
	error = dx + dy

	while true
		plot(x0, y0)
		if x0 == x1 && y0 == y1 break
		e2 = 2 * error
		if e2 >= dy
			if x0 == x1 break
			error = error + dy
			x0 = x0 + sx
		end if
		if e2 <= dx
			if y0 == y1 break
			error = error + dx
			y0 = y0 + sy
		end if
	end while
*/

/*
 dx = abs(x1 - x2);
	  dy = abs(y1 - y2);
	  p = 2 * dy - dx;
	  if(x1 > x2)
	  {
			x = x2;
			y = y2;
			end = x1;
	  }
	  else
	  {
			x = x1;
			y = y1;
			end = x2;
	  }
	  putpixel(x, y, 10);
	  while(x < end)
	  {
			x = x + 1;
			if(p < 0)
			{
				  p = p + 2 * dy;
			}
			else
			{
				  y = y + 1;
				  p = p + 2 * (dy - dx);
			}
			putpixel(x, y, 10);
	  }
*/

void	fdf_frame(void *param)
{
	t_fdf	*fdf;
	int		x;
	int		y;
	int		color;

	y = 0;
	color = 0xffffffff;
	fdf = (t_fdf *)param;
	fdf->x_offset = (WINDOW_WIDTH / 2) - ((fdf->map_width / 2) * SCALE);
	fdf->y_offset = (WINDOW_HEIGHT / 2) - ((fdf->map_height / 2) * SCALE);
	clear_image(fdf);
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x + 1 < fdf->map_width)
				drawline(fdf, fdf->vecmap[y * fdf->map_width + x],
					fdf->vecmap[y * fdf->map_width + x + 1]);
			if (y + 1 < fdf->map_height)
				drawline(fdf, fdf->vecmap[y * fdf->map_width + x],
					fdf->vecmap[(y + 1) * fdf->map_width + x]);
			x++;
		}
		y++;
	}
}

void	fdf_loop(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &fdf_keyhook, (void *)fdf);
	mlx_loop_hook(fdf->mlx, fdf_frame, (void *)fdf);
	mlx_loop(fdf->mlx);
}
