/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 18:04:18 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 11:51:13 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

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
