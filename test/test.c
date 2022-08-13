/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/02 15:38:03 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/14 01:36:42 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

static t_point3d	fill_vec(int x, int y, int z)
{
	t_point3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

// static t_mat4x4	make_pers_matrix(void)
// {
// 	int			i;
// 	int			j;

// 	float		ffov_rad;
// 	float		fnear = 0.4;
// 	float		ffar = 1000;
// 	float		ffov = 90;
// 	float		faspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
// 	t_mat4x4	proj;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			proj.m[i][j] = 0.0f;
// 			j++;
// 		}
// 		i++;
// 	}
// 	ffov_rad = 1 / tanf(ffov * .5 / 180 * 3.14159);
// 	proj.m[0][0] = faspect_ratio * ffov_rad;
// 	proj.m[1][1] = ffov_rad;
// 	proj.m[2][2] = ffar / (ffar - fnear);
// 	proj.m[3][2] = (-ffar * fnear) / (ffar - fnear);
// 	proj.m[2][3] = 1;
// 	proj.m[3][3] = 0;
// 	return (proj);
// }

// static int	check_pers_matrix()
// {
// 	t_mat4x4	proj;

// 	proj = make_pers_matrix();
// 	return (0);
// }

// t_point3d	perspective_transform(t_point3d p, t_fdf *fdf)
// {
// 	t_point3d	new_p;

// 	p.z += 100;
// 	p.z += fdf->z_offset >> 2;
// 	p.x += (fdf->x_offset >> 2);
// 	p.y += (fdf->y_offset >> 2);
// 	multiply_matrix_vec(&p, &new_p, fdf->proj);
// 	// new_p.x += 1.0f;
// 	// new_p.y += 1.0f;
// 	new_p.z = (new_p.z + 1.0f) * .5;
// 	new_p.x *= 1000;
// 	new_p.y *= 1000;
// 	new_p.z *= 100;
// 	// new_p.z += 0.4;
// 	new_p.x += WINDOW_WIDTH >> 1;
// 	new_p.y += WINDOW_HEIGHT >> 1;
// 	// new_p.z += 500;
// 	return (new_p);
// }

static void	test_init(t_fdf *fdf)
{
	fdf->z_offset = 0;
	fdf->z_scaling = 0.1;
	fdf->x_rot = 0;
	fdf->y_rot = 0;
	fdf->z_rot = 0;
	fdf->scale = 10;
	new_perspective_init(fdf);
}

static int	compare_vecs(t_point3d a, t_point3d b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (0);
	return (1);
}

int	main(void)
{
	t_fdf	fdf;
	t_point3d	temp;
	t_point3d	pa;
	t_point3d	pb;
	t_point3d	pc;
	t_point3d	pd;
	t_point3d	pe;
	t_point3d	pf;
	t_point3d	pg;
	t_point3d	ph;

	test_init(&fdf);
	pa = fill_vec(1, 1, 1);
	multiply_matrix_vec(&pa, &temp, fdf.proj);
	if (compare_vecs(pa, temp))
		printf("1, 1, 1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	pb = fill_vec(-1, 1, 1);
	multiply_matrix_vec(&pb, &temp, fdf.proj);
	if (compare_vecs(pb, temp))
		printf("-1, 1, 1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	pc = fill_vec(-1, 1, -1);
	multiply_matrix_vec(&pc, &temp, fdf.proj);
	if (compare_vecs(pc, temp))
		printf("-1, 1, -1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	pd = fill_vec(1, 1, -1);
	multiply_matrix_vec(&pd, &temp, fdf.proj);
	if (compare_vecs(pd, temp))
		printf("1, 1, -1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	pe = fill_vec(1, -1, 1);
	multiply_matrix_vec(&pe, &temp, fdf.proj);
	if (compare_vecs(pe, temp))
		printf("1, 1, -1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	pf = fill_vec(-1, -1, 1);
	multiply_matrix_vec(&pf, &temp, fdf.proj);
	if (compare_vecs(pf, temp))
		printf("1, 1, -1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	pg = fill_vec(-1, -1, -1);
	multiply_matrix_vec(&pg, &temp, fdf.proj);
	if (compare_vecs(pg, temp))
		printf("1, 1, -1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	ph = fill_vec(1, -1, -1);
	multiply_matrix_vec(&ph, &temp, fdf.proj);
	if (compare_vecs(ph, temp))
		printf("1, 1, -1 bad, result: %f %f %f\n", temp.x, temp.y, temp.z);

	printf("0xFF = %i, 0xFF = %i\n", ft_hextoi("FF"), 0xFF);
	t_rgb	rgb;
	t_hsv	hsv;

	rgb = set_rgb(1, 0, 0);
	hsv = rgb_to_hsv(rgb);
	printf("Red: h: %f, s: %f, v: %f\n", hsv.h, hsv.s, hsv.v);
	rgb = set_rgb(0, 1, 0);
	hsv = rgb_to_hsv(rgb);
	printf("Green: h: %f, s: %f, v: %f\n", hsv.h, hsv.s, hsv.v);
	rgb = set_rgb(0, 0, 1);
	hsv = rgb_to_hsv(rgb);
	printf("Blue: h: %f, s: %f, v: %f\n", hsv.h, hsv.s, hsv.v);
}
