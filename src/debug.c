/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 15:00:47 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/30 14:25:25 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

void	error_message(int id)
{
	if (id == -1)
		ft_printf("Error!\n - Invalid Filepath.\n");
	else if (id == -2)
		ft_printf("Error!\n - File reading failed.\n");
	else if (id == -2)
		ft_printf("Error!\n - String allocation failed.\n");
	else if (id == -3)
		ft_printf("Error!\n - Not a '.fdf' file.\n");
	else if (id == -4)
		ft_printf("No argument given. Or incorrect argument count\n");
}

void	print_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map_height)
	{
		j = 0;
		while (j < fdf->map_width)
		{
			ft_printf("%i ", fdf->map[(i * fdf->map_width) + j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
