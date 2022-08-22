/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   projection_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 11:38:45 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 11:38:54 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat3x3	set_mat3x3_0(t_mat3x3 m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			m.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (m);
}

t_mat4x4	set_mat4x4_0(t_mat4x4 m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (m);
}
