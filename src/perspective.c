/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perspective.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 12:07:51 by dritsema      #+#    #+#                 */
/*   Updated: 2022/07/26 12:13:29 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "libft.h"
#include "MLX42.h"

t_mat4x4	perspective_transform(t_3dvec p, t_fdf *fdf)
{
	float	fnear;
	float	ffar;
	float	ffov;
	float	f_aspect_ratio;

	fnear = 0.1;
	ffar = 1000;
	ffov = 90;
	f_aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;
}
