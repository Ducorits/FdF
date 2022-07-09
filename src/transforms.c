/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transforms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/09 14:55:24 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/09 16:35:54 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

t_3dvec	rotate_vec(t_3dvec a, float degrees)
{
	degrees = degrees;
	a.x = -a.y;
	a.y = a.x;
	return (a);
}
