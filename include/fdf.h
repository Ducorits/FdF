/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:41:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/12 14:40:08 by dritsema      ########   odam.nl         */
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

typedef struct s_ivec
{
	int	x;
	int	y;
	int	z;
}	t_ivec;
typedef struct s_fvec
{
	float	x;
	float	y;
	float	z;
}	t_fvec;

typedef struct s_point3d
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point3d;

typedef struct s_mat4x4
{
	float	m[4][4];
}	t_mat4x4;

typedef struct s_mat3x3
{
	float	m[3][3];
}	t_mat3x3;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			*depth_buffer;
	int			*map;
	int			map_width;
	int			map_height;
	// t_fvec		*vecmap;
	t_point3d	*map3d;
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
	t_mat3x3	rotation;
	float		fnear;
	float		ffar;
	float		ffov;
	float		faspect_ratio;
	float		y_aratio;
	float		ffov_rad;
	float		zoom;
	int			lowest_p;
	int			highest_p;
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
int			in_window(t_ivec p);
t_ivec		veci(t_point3d p);

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
// t_fvec		rotate_vec(t_fvec a, float degrees);
t_point3d	rotate_vecx(t_point3d a, float degrees);
t_point3d	rotate_vecy(t_point3d a, float degrees);
t_point3d	rotate_vecz(t_point3d a, float degrees);
void		multiply_matrix_vec(t_point3d *i, t_point3d *o, t_mat4x4 m);
t_point3d	transform_point(t_point3d p, t_fdf *fdf);
t_point3d	perspective_transform(t_point3d p, t_fdf *fdf);

// for debug
int			error_check(char *file_name);
void		error_message(int id);
void		print_map(t_fdf *fdf);

// Line Drawing
t_point3d	get_point(int x, int y, t_fdf *fdf);
void		drawline(t_fdf *fdf, t_ivec a, t_ivec b, t_point3d af, t_point3d bf);

// Perspective stuff
void		new_perspective_update(t_fdf *fdf);
void		new_perspective_init(t_fdf *fdf);

// Rotation
t_point3d	rotate_vec(t_fdf *fdf, t_point3d i);
t_mat3x3	rotate_around_x(t_mat3x3 r, float deg);
t_mat3x3	rotate_around_y(t_mat3x3 r, float deg);
t_mat3x3	rotate_around_z(t_mat3x3 r, float deg);

#endif // FDF_H
