/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:41:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/02 16:13:34 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"

# define WINDOW_WIDTH 1980
# define WINDOW_HEIGHT 1080
# define SCALE 20

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_intvec
{
	int	x;
	int	y;
	int	z;
}	t_intvec;
typedef struct s_3dvec
{
	float	x;
	float	y;
	float	z;
}	t_3dvec;

typedef struct s_mat4x4
{
	float	m[4][4];
}	t_mat4x4;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			*map;
	int			map_width;
	int			map_height;
	t_3dvec		*vecmap;
	int			x_offset;
	int			y_offset;
	int			z_offset;
	int			mouse_x;
	int			mouse_y;
	int			last_mouse_x;
	int			last_mouse_y;
	float		z_scaling;
	float		scale;
	int			rotating;
	float		x_rot;
	float		y_rot;
	float		z_rot;
	t_mat4x4	proj;
	float		fnear;
	float		ffar;
	float		ffov;
	float		faspect_ratio;
	float		y_aratio;
	float		ffov_rad;
}	t_fdf;

// Inits
t_fdf		fdf_init(char *file_name);
int			map_init(char *file_name, t_fdf *fdf);
void		perspective_init(t_fdf *fdf);

// fdf loop
void		fdf_loop(t_fdf *fdf);
void		perspective_update(t_fdf *fdf);

// fdf hooks
void		fdf_keycheck(t_fdf *fdf);
void		fdf_scrollhook(double xdelta, double ydelta, void *param);

// Utils
void		fdf_free(t_fdf *fdf);
void		fdf_exit(const char *fname, int error);
void		clear_image(t_fdf *fdf);
int			in_window(t_intvec p);
t_intvec	veci(t_3dvec vecf);

// Map utils
void		fill_map(char *str_map, t_fdf *fdf);
void		rotate_map(t_fdf *fdf, float degrees);
void		scale_map(t_fdf *fdf, float scale);
void		reset_map(t_fdf *fdf);
void		move_map(t_fdf *fdf, int dir);
void		rotate_x(t_fdf *fdf, float degrees);
void		rotate_y(t_fdf *fdf, float degrees);
void		rotate_z(t_fdf *fdf, float degrees);

// Transforms
t_3dvec		rotate_vec(t_3dvec a, float degrees);
t_3dvec		rotate_vecx(t_3dvec a, float degrees);
t_3dvec		rotate_vecy(t_3dvec a, float degrees);
t_3dvec		rotate_vecz(t_3dvec a, float degrees);
void		multiply_matrix_vec(t_3dvec *i, t_3dvec *o, t_mat4x4 m);
t_point		transform(t_3dvec p3d, t_fdf *fdf);
t_3dvec		perspective_transform(t_3dvec p, t_fdf *fdf);

// for debug
int			error_check(char *file_name);
void		error_message(int id);
void		print_map(t_fdf *fdf);

// Line Drawing
t_3dvec		get_point(int x, int y, t_fdf *fdf);
void		drawline(t_fdf *fdf, t_intvec a, t_intvec b, t_3dvec af, t_3dvec bf);

#endif // FDF_H
