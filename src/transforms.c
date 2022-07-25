/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transforms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/25 18:34:08 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/fdf.h"

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

t_point	transform(t_3dvec a, t_3dvec b, t_fdf *fdf)
{
	a = scale_vec(a, fdf->scale);
	b = scale_vec(b, fdf->scale);
}
