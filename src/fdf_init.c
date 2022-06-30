/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 13:35:01 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/30 16:09:06 by dritsema      ########   odam.nl         */
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
	fdf->mlx = mlx_init(100, 100, "fdf", 1);
	return (fdf);
}
