/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transforms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/28 15:18:28 by dritsema      ########   odam.nl         */
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
	if (w != 0)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}

t_3dvec	scale_vec(t_3dvec a, float scalar)
{
	a.x *= scalar;
	a.y *= scalar;
	a.z *= scalar;
	return (a);
}

t_3dvec	rotate_vec(t_3dvec a, float degrees)
{
	t_3dvec	temp;

	temp = a;
	a.x = (temp.x * cos(degrees)) - (temp.y * sin(degrees));
	a.y = (temp.x * sin(degrees)) + (temp.y * cos(degrees));
	return (a);
}

t_3dvec	rotate_vecx(t_3dvec a, float degrees)
{
	t_3dvec	temp;

	temp = a;
	a.x = (temp.x * 1) + (temp.y * 0) + (temp.z * 0);
	a.y = (temp.x * 0) + (temp.y * cos(degrees)) - (temp.z * sin(degrees));
	a.z = (temp.x * 0) + (temp.y * sin(degrees)) + (temp.z * cos(degrees));
	return (a);
}

t_point	transform(t_3dvec p3d, t_fdf *fdf)
{
	t_point	p;

	p3d = scale_vec(p3d, fdf->scale);
	p.x = p3d.x + fdf->x_offset;
	p.y = p3d.y + fdf->y_offset - (p3d.z * fdf->z_scaling);
	return (p);
}
