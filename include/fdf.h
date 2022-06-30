/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:41:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/30 16:10:00 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"

typedef struct s_fdf
{
	mlx_t	*mlx;
	int		*map;
	int		map_width;
	int		map_height;
}	t_fdf;

// fdf loop
void	fdf_loop(t_fdf *fdf);

// Utils
void	fill_map(char *str_map, t_fdf *fdf);
t_fdf	*fdf_init(char *file_name);
int		map_init(char *file_name, t_fdf *fdf);
void	fdf_free(t_fdf *fdf);
void	fdf_exit(const char *fname, int error);

// for debug
int		error_check(char *file_name);
void	error_message(int id);
void	print_map(t_fdf *fdf);

#endif // FDF_H
