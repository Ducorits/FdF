/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 13:35:01 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/21 19:14:52 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <unistd.h>

t_fdf	fdf_init(char *file_name)
{
	t_fdf	fdf;
	char	*window_name;

	window_name = ft_strjoin("fdf - ", file_name);
	map_init(file_name, &fdf);
	fdf.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, window_name, 1);
	free(window_name);
	if (fdf.mlx == 0)
		fdf_exit("fdf_init", 7);
	fdf.image = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf.depth_buffer = malloc((fdf.image->height * fdf.image->width)
			* sizeof(int));
	if (fdf.image == 0 || fdf.depth_buffer == 0)
		fdf_exit("fdf_init", 8);
	if (mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) == -1)
		fdf_exit("fdf_init", 9);
	fdf.projection_mode = 2;
	fdf.render_mode = 0;
	render_init(&fdf);
	return (fdf);
}
