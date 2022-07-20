/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transforms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/20 16:38:00 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/fdf.h"

t_3dvec	rotate_vec(t_3dvec a, float degrees)
{
	t_3dvec	temp;

	temp = a;
	a.x = (temp.x * cos(degrees)) - (temp.y * sin(degrees));
	a.y = (temp.x * sin(degrees)) + (temp.y * cos(degrees));
	return (a);
}
