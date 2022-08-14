/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 16:07:07 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/14 16:17:34 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rgb_to_int(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}
