/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 13:35:01 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/21 01:11:27 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <unistd.h>

t_fdf	*fdf_init(char *file_name)
{
	t_fdf	*fdf;
	char	*window_name;

	fdf = malloc(sizeof(t_fdf));
	window_name = ft_strjoin("fdf - ", file_name);
	map_init(file_name, fdf);
	fdf->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, window_name, 1);
	free(window_name);
	if (fdf->mlx == 0)
		fdf_exit("fdf_init", 7);
	fdf->render = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (fdf->render == 0)
		fdf_exit("fdf_init", 8);
	if (mlx_image_to_window(fdf->mlx, fdf->render, 0, 0) == -1)
		fdf_exit("fdf_init", 9);
	fdf->x_offset = (WINDOW_WIDTH / 2);
	fdf->y_offset = (WINDOW_HEIGHT / 2);
	fdf->z_scaling = 0.5;
	return (fdf);
}
