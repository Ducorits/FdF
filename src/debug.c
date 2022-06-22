/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 15:00:47 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/22 15:07:19 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	print_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (fdf->map[i])
	{
		j = 0;
		while (fdf->map[i][j])
		{
			ft_printf("%i ", fdf->map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
