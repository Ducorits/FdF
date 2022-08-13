/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hsv.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 21:46:32 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/14 01:40:07 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static float	get_max_rgb(t_rgb rgb)
{
	if (rgb.r >= rgb.g && rgb.r >= rgb.b)
		return (rgb.r);
	else if (rgb.g >= rgb.r && rgb.g >= rgb.b)
		return (rgb.g);
	else
		return (rgb.b);
}

static float	get_min_rgb(t_rgb rgb)
{
	if (rgb.r <= rgb.g && rgb.r <= rgb.b)
		return (rgb.r);
	else if (rgb.g <= rgb.r && rgb.g <= rgb.b)
		return (rgb.g);
	else
		return (rgb.b);
}

t_hsv	rgb_to_hsv(t_rgb rgb)
{
	t_hsv	hsv;
	float	max;
	float	min;

	min = get_min_rgb(rgb);
	max = get_max_rgb(rgb);
	if (rgb.r == max)
		hsv.h = (0 + (rgb.g - rgb.b) / (max - min)) * 60;
	else if (rgb.g == max)
		hsv.h = (2 + (rgb.b - rgb.r) / (max - min)) * 60;
	else if (rgb.b == max)
		hsv.h = (4 + (rgb.r - rgb.g) / (max - min)) * 60;
	hsv.s = (max - min) / max;
	hsv.v = max;
	return (hsv);
}

t_rgb	set_rgb(float r, float g, float b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

t_rgb	hsv_to_rgb(t_hsv hsv)
{
	t_hsv_vars	vars;

	if (hsv.s == 0)
		return (set_rgb(hsv.v, hsv.v, hsv.v));
	vars.hi = floor(hsv.h / 60);
	vars.f = (hsv.h / 60) - vars.hi;
	vars.p = hsv.v * (1 - hsv.s);
	vars.q = hsv.v * (1 - (vars.f * hsv.s));
	vars.t = hsv.v * (1 - (1 - vars.f) * hsv.s);
	if (vars.hi == 0)
		return (set_rgb(hsv.v, vars.t, vars.p));
	if (vars.hi == 1)
		return (set_rgb(vars.q, hsv.v, vars.p));
	if (vars.hi == 2)
		return (set_rgb(vars.p, hsv.v, vars.t));
	if (vars.hi == 3)
		return (set_rgb(vars.p, vars.q, hsv.v));
	if (vars.hi == 4)
		return (set_rgb(vars.t, vars.p, hsv.v));
	if (vars.hi == 5)
		return (set_rgb(hsv.v, vars.p, vars.q));
	return (set_rgb(0, 0, 0));
}
