/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:41:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/09 15:14:24 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"

# define WINDOW_WIDTH 1980
# define WINDOW_HEIGHT 1080
# define SCALE 20

typedef struct s_3dvec
{
	int	x;
	int	y;
	int	z;
}	t_3dvec;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*render;
	int			*map;
	int			map_width;
	int			map_height;
	t_3dvec		*vecmap;
	int			x_offset;
	int			y_offset;
}	t_fdf;

// fdf loop
void	fdf_loop(t_fdf *fdf);

// fdf hooks
void	fdf_keyhook(mlx_key_data_t keydata, void *param);

// Utils
t_fdf	*fdf_init(char *file_name);
void	fdf_free(t_fdf *fdf);
void	fdf_exit(const char *fname, int error);
void	clear_image(t_fdf *fdf);

// Map utils
int		map_init(char *file_name, t_fdf *fdf);
void	fill_map(char *str_map, t_fdf *fdf);
void	rotate_map(t_fdf *fdf, float degrees);
void	scale_map(t_fdf *fdf, float scale);
void	reset_map(t_fdf *fdf);

// Transforms
t_3dvec	rotate_vec(t_3dvec a, float degrees);

// for debug
int		error_check(char *file_name);
void	error_message(int id);
void	print_map(t_fdf *fdf);

#endif // FDF_H
