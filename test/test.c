/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/02 15:38:03 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/15 20:26:06 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

void	print_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map_height)
	{
		j = 0;
		while (j < fdf->map_width)
		{
			ft_printf("%i ", fdf->map[(i * fdf->map_width) + j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

static t_point3d	fill_vec(int x, int y, int z)
{
	t_point3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

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

	printf("\nHextoi:     Printf:\n0xFF = %i, 0xFF = %i\n\n", ft_hextoi("FF"), 0xFF);
	t_rgb	rgb;
	t_hsv	hsv;

	rgb = set_rgb(1, 0, 0);
	hsv = rgb_to_hsv(rgb);
	printf("RGB to HSV. Red:   h: %-10f, s: %f, v: %f\n", hsv.h, hsv.s, hsv.v);
	rgb = hsv_to_rgb(hsv);
	printf("HSV to RGB, Red:   r: %-10f, g: %f, b: %f\n", rgb.r, rgb.g, rgb.b);
	rgb = set_rgb(0, 1, 0);
	hsv = rgb_to_hsv(rgb);
	printf("RGB to HSV. Green: h: %-10f, s: %f, v: %f\n", hsv.h, hsv.s, hsv.v);
	rgb = hsv_to_rgb(hsv);
	printf("HSV to RGB, Green: r: %-10f, g: %f, b: %f\n", rgb.r, rgb.g, rgb.b);
	rgb = set_rgb(0, 0, 1);
	hsv = rgb_to_hsv(rgb);
	printf("RGB to HSV. Blue:  h: %-10f, s: %f, v: %f\n", hsv.h, hsv.s, hsv.v);
	rgb = hsv_to_rgb(hsv);
	printf("HSV to RGB. Blue:  r: %-10f, g: %f, b: %f\n", rgb.r, rgb.g, rgb.b);
}
