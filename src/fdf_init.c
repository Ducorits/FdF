/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 13:35:01 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/05 18:53:23 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <unistd.h>

t_fdf	*fdf_init(char *file_name)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	map_init(file_name, fdf);
	fdf->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "fdf", 1);
	if (fdf->mlx == 0)
		fdf_exit("fdf_init", 7);
	fdf->render = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (fdf->render == 0)
		fdf_exit("fdf_init", 8);
	if (mlx_image_to_window(fdf->mlx, fdf->render, 0, 0) == -1)
		fdf_exit("fdf_init", 9);
	return (fdf);
}
