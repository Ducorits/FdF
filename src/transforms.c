/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transforms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/08 14:35:26 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/fdf.h"

void	multiply_matrix_vec(t_3dvec *i, t_3dvec *o, t_mat4x4 m)
{
	float	w;

	o->x = i->x * m.m[0][0] + i->y * m.m[1][0] + i->z * m.m[2][0] + m.m[3][0];
	o->y = i->x * m.m[0][1] + i->y * m.m[1][1] + i->z * m.m[2][1] + m.m[3][1];
	o->z = i->x * m.m[0][2] + i->y * m.m[1][2] + i->z * m.m[2][2] + m.m[3][2];
	w = i->x * m.m[0][3] + i->y * m.m[1][3] + i->z * m.m[2][3] + m.m[3][3];
	if (w != 1)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}

t_3dvec	rotate_vec(t_fdf *fdf, t_3dvec i)
{
	t_3dvec		o;
	t_mat3x3	m;

	m = fdf->rotation;
	o = i;
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2];
	return (o);
}

t_3dvec	scale_vec(t_3dvec a, float scalar)
{
	a.x *= scalar;
	a.y *= scalar;
	a.z *= scalar;
	return (a);
}

void	rotate_around_x(t_fdf *fdf, float deg)
{
	t_mat3x3	m;

	m = fdf->rotation;
	fdf->rotation.m[0][0] = (m.m[0][0] * 1) + (m.m[0][1] * 0) + (m.m[0][2] * 0);
	fdf->rotation.m[1][0] = (m.m[1][0] * 1) + (m.m[1][1] * 0) + (m.m[1][2] * 0);
	fdf->rotation.m[2][0] = (m.m[2][0] * 1) + (m.m[2][1] * 0) + (m.m[2][2] * 0);

	fdf->rotation.m[0][1] = (m.m[0][0] * 0) + (m.m[0][1] * cos(deg)) + (m.m[0][2] * sin(deg));
	fdf->rotation.m[1][1] = (m.m[1][0] * 0) + (m.m[1][1] * cos(deg)) + (m.m[1][2] * sin(deg));
	fdf->rotation.m[2][1] = (m.m[2][0] * 0) + (m.m[2][1] * cos(deg)) + (m.m[2][2] * sin(deg));

	fdf->rotation.m[0][2] = (m.m[0][0] * 0) - (m.m[0][1] * sin(deg)) + (m.m[0][2] * cos(deg));
	fdf->rotation.m[1][2] = (m.m[1][0] * 0) - (m.m[1][1] * sin(deg)) + (m.m[1][2] * cos(deg));
	fdf->rotation.m[2][2] = (m.m[2][0] * 0) - (m.m[2][1] * sin(deg)) + (m.m[2][2] * cos(deg));
}

void	rotate_around_y(t_fdf *fdf, float deg)
{
	t_mat3x3	m;

	m = fdf->rotation;
	fdf->rotation.m[0][0] = (m.m[0][0] * cos(deg)) + (m.m[0][1] * 0) - (m.m[0][2] * sin(deg));
	fdf->rotation.m[1][0] = (m.m[1][0] * cos(deg)) + (m.m[1][1] * 0) - (m.m[1][2] * sin(deg));
	fdf->rotation.m[2][0] = (m.m[2][0] * cos(deg)) + (m.m[2][1] * 0) - (m.m[2][2] * sin(deg));

	fdf->rotation.m[0][1] = (m.m[0][0] * 0) + (m.m[0][1] * 1) + (m.m[0][2] * 0);
	fdf->rotation.m[1][1] = (m.m[1][0] * 0) + (m.m[1][1] * 1) + (m.m[1][2] * 0);
	fdf->rotation.m[2][1] = (m.m[2][0] * 0) + (m.m[2][1] * 1) + (m.m[2][2] * 0);

	fdf->rotation.m[1][2] = (m.m[1][0] * sin(deg)) + (m.m[1][1] * 0) + (m.m[1][2] * cos(deg));
	fdf->rotation.m[0][2] = (m.m[0][0] * sin(deg)) + (m.m[0][1] * 0) + (m.m[0][2] * cos(deg));
	fdf->rotation.m[2][2] = (m.m[2][0] * sin(deg)) + (m.m[2][1] * 0) + (m.m[2][2] * cos(deg));
}

void	rotate_around_z(t_fdf *fdf, float deg)
{
	t_mat3x3	m;

	m = fdf->rotation;
	fdf->rotation.m[0][0] = (m.m[0][0] * cos(deg)) + (m.m[0][1] * sin(deg)) + (m.m[0][2] * 0);
	fdf->rotation.m[1][0] = (m.m[1][0] * cos(deg)) + (m.m[1][1] * sin(deg)) + (m.m[1][2] * 0);
	fdf->rotation.m[2][0] = (m.m[2][0] * cos(deg)) + (m.m[2][1] * sin(deg)) + (m.m[2][2] * 0);

	fdf->rotation.m[0][1] = (m.m[0][0] * -sin(deg)) + (m.m[0][1] * cos(deg)) + (m.m[0][2] * 0);
	fdf->rotation.m[1][1] = (m.m[1][0] * -sin(deg)) + (m.m[1][1] * cos(deg)) + (m.m[1][2] * 0);
	fdf->rotation.m[2][1] = (m.m[2][0] * -sin(deg)) + (m.m[2][1] * cos(deg)) + (m.m[2][2] * 0);

	fdf->rotation.m[0][2] = (m.m[0][0] * 0) + (m.m[0][1] * 0) + (m.m[0][2] * 1);
	fdf->rotation.m[1][2] = (m.m[1][0] * 0) + (m.m[1][1] * 0) + (m.m[1][2] * 1);
	fdf->rotation.m[2][2] = (m.m[2][0] * 0) + (m.m[2][1] * 0) + (m.m[2][2] * 1);
}

t_3dvec	transform_point(t_3dvec p, t_fdf *fdf)
{
	p.z = p.z * fdf->z_scaling;
	p.x *= fdf->scale;
	p.y *= fdf->scale;
	p = rotate_vec(fdf, p);
	return (p);
}
