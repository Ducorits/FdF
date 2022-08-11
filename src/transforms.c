/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transforms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/11 15:05:43 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/fdf.h"

void	multiply_matrix_vec(t_point3d *i, t_point3d *o, t_mat4x4 m)
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

t_point3d	rotate_point(t_fdf *fdf, t_point3d i)
{
	t_point3d	o;
	t_mat3x3	m;

	m = fdf->rotation;
	o = i;
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2];
	return (o);
}

t_point3d	scale_vec(t_point3d a, float scalar)
{
	a.x *= scalar;
	a.y *= scalar;
	a.z *= scalar;
	return (a);
}

t_mat3x3	rotate_around_x(t_mat3x3 r, float d)
{
	t_mat3x3	m;

	m = r;
	r.m[0][0] = (m.m[0][0] * 1) + (m.m[0][1] * 0) + (m.m[0][2] * 0);
	r.m[1][0] = (m.m[1][0] * 1) + (m.m[1][1] * 0) + (m.m[1][2] * 0);
	r.m[2][0] = (m.m[2][0] * 1) + (m.m[2][1] * 0) + (m.m[2][2] * 0);

	r.m[0][1] = (m.m[0][0] * 0) + (m.m[0][1] * cos(d)) + (m.m[0][2] * sin(d));
	r.m[1][1] = (m.m[1][0] * 0) + (m.m[1][1] * cos(d)) + (m.m[1][2] * sin(d));
	r.m[2][1] = (m.m[2][0] * 0) + (m.m[2][1] * cos(d)) + (m.m[2][2] * sin(d));

	r.m[0][2] = (m.m[0][0] * 0) - (m.m[0][1] * sin(d)) + (m.m[0][2] * cos(d));
	r.m[1][2] = (m.m[1][0] * 0) - (m.m[1][1] * sin(d)) + (m.m[1][2] * cos(d));
	r.m[2][2] = (m.m[2][0] * 0) - (m.m[2][1] * sin(d)) + (m.m[2][2] * cos(d));
	return (r);
}

t_mat3x3	rotate_around_y(t_mat3x3 r, float d)
{
	t_mat3x3	m;

	m = r;
	r.m[0][0] = (m.m[0][0] * cos(d)) + (m.m[0][1] * 0) - (m.m[0][2] * sin(d));
	r.m[1][0] = (m.m[1][0] * cos(d)) + (m.m[1][1] * 0) - (m.m[1][2] * sin(d));
	r.m[2][0] = (m.m[2][0] * cos(d)) + (m.m[2][1] * 0) - (m.m[2][2] * sin(d));

	r.m[0][1] = (m.m[0][0] * 0) + (m.m[0][1] * 1) + (m.m[0][2] * 0);
	r.m[1][1] = (m.m[1][0] * 0) + (m.m[1][1] * 1) + (m.m[1][2] * 0);
	r.m[2][1] = (m.m[2][0] * 0) + (m.m[2][1] * 1) + (m.m[2][2] * 0);

	r.m[1][2] = (m.m[1][0] * sin(d)) + (m.m[1][1] * 0) + (m.m[1][2] * cos(d));
	r.m[0][2] = (m.m[0][0] * sin(d)) + (m.m[0][1] * 0) + (m.m[0][2] * cos(d));
	r.m[2][2] = (m.m[2][0] * sin(d)) + (m.m[2][1] * 0) + (m.m[2][2] * cos(d));
	return (r);
}

t_mat3x3	rotate_around_z(t_mat3x3 r, float d)
{
	t_mat3x3	m;

	m = r;
	r.m[0][0] = (m.m[0][0] * cos(d)) + (m.m[0][1] * sin(d)) + (m.m[0][2] * 0);
	r.m[1][0] = (m.m[1][0] * cos(d)) + (m.m[1][1] * sin(d)) + (m.m[1][2] * 0);
	r.m[2][0] = (m.m[2][0] * cos(d)) + (m.m[2][1] * sin(d)) + (m.m[2][2] * 0);

	r.m[0][1] = (m.m[0][0] * -sin(d)) + (m.m[0][1] * cos(d)) + (m.m[0][2] * 0);
	r.m[1][1] = (m.m[1][0] * -sin(d)) + (m.m[1][1] * cos(d)) + (m.m[1][2] * 0);
	r.m[2][1] = (m.m[2][0] * -sin(d)) + (m.m[2][1] * cos(d)) + (m.m[2][2] * 0);

	r.m[0][2] = (m.m[0][0] * 0) + (m.m[0][1] * 0) + (m.m[0][2] * 1);
	r.m[1][2] = (m.m[1][0] * 0) + (m.m[1][1] * 0) + (m.m[1][2] * 1);
	r.m[2][2] = (m.m[2][0] * 0) + (m.m[2][1] * 0) + (m.m[2][2] * 1);
	return (r);
}

t_point3d	transform_point(t_point3d p, t_fdf *fdf)
{
	p.z = p.z * fdf->z_scaling;
	p.x *= fdf->scale;
	p.y *= fdf->scale;
	p = rotate_point(fdf, p);
	return (p);
}
