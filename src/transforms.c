/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transforms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/19 13:58:29 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/fdf.h"

t_3dvec	rotate_vec(t_3dvec a, float degrees)
{
	a.x = a.x * cos(degrees) - a.y * sin(degrees);
	a.y = a.x * sin(degrees) + a.y * cos(degrees);
	return (a);
}
