/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:41:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/19 13:31:28 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"

# define WINDOW_WIDTH 1980
# define WINDOW_HEIGHT 1080
# define SCALE 20

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

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
	float			x;
	float			y;
	float			z;
	int				r;
	int				g;
	int				b;
	unsigned int	color;
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
	t_point3d	*map3d;
	int			x_offset;
	int			y_offset;
	int			z_offset;
	int			persz_off;
	int			mouse_x;
	int			mouse_y;
	int			last_mouse_x;
	int			last_mouse_y;
	float		z_scaling;
	float		scale;
	t_mat4x4	pers;
	t_mat4x4	orth;
	t_mat3x3	rotation;
	float		fnear;
	float		ffar;
	float		ffov;
	float		faspect_ratio;
	float		ffov_rad;
	float		zoom;
	float		lowest_z;
	float		highest_z;
	int			render_mode;
}	t_fdf;

// Inits
t_fdf		fdf_init(char *file_name);
int			map_init(char *file_name, t_fdf *fdf);

// fdf loop
void		fdf_loop(t_fdf *fdf);

// fdf hooks
void		fdf_keycheck(t_fdf *fdf);
void		fdf_scrollhook(double xdelta, double ydelta, void *param);

// Utils
void		fdf_free(t_fdf *fdf);
void		fdf_exit(const char *fname, int error);
void		clear_image(t_fdf *fdf);
int			in_window(t_ivec p, t_fdf *fdf);
t_ivec		veci(t_point3d p);
void		get_height_extremes(t_fdf *fdf);

// Matrix Utilities
t_mat3x3	set_mat3x3_0(t_mat3x3 m);
t_mat4x4	set_mat4x4_0(t_mat4x4 m);

// Map utils
void		set_maps(char *str_map, t_fdf *fdf);
void		scale_map(t_fdf *fdf, float scale);
void		move_map(t_fdf *fdf, int dir);
int			skip_hex(char *str_map);

// Transforms
void		multiply_matrix_vec(t_point3d *i, t_point3d *o, t_mat4x4 m);
t_point3d	transform_point(t_point3d p, t_fdf *fdf);

// for debug
int			error_check(char *file_name);
void		error_message(int id);

// Line Drawing
t_point3d	get_point(int x, int y, t_fdf *fdf);
void		drawline(t_fdf *fdf, t_ivec a, t_ivec b, t_point3d af, t_point3d bf);

// Perspective stuff
void		perspective_update(t_fdf *fdf);
void		perspective_init(t_fdf *fdf);
t_point3d	perspective_transform(t_point3d p, t_fdf *fdf);

// Orthographic functions
void		orthographic_init(t_fdf *fdf);
void		orthographic_update(t_fdf *fdf);
t_point3d	orthographic_transform(t_point3d p, t_fdf *fdf);

// isometric functions
void		isometric_init(t_fdf *fdf);

// Rotation
t_point3d	rotate_point(t_fdf *fdf, t_point3d i);
t_mat3x3	rotate_around_x(t_mat3x3 r, float deg);
t_mat3x3	rotate_around_y(t_mat3x3 r, float deg);
t_mat3x3	rotate_around_z(t_mat3x3 r, float deg);

// Color functions
t_point3d	set_height_color(t_point3d p, t_fdf *fdf);
t_point3d	get_point_color(t_point3d p, char *str_map);
t_rgb		set_rgb(float r, float g, float b);
int			rgb_to_int(int r, int g, int b);
int			rgb_interpolate(int c1, int c2,
				int step_count, int step);

// Render Functions
t_point3d	projection_transform(t_point3d p, t_fdf *fdf);
void		render_init(t_fdf *fdf);
void		render_update(t_fdf *fdf);
void		update_image(t_fdf *fdf);

#endif // FDF_H
