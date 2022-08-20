/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_maps.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 20:32:52 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/20 14:49:31 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <unistd.h>

void	get_map_size(char *str_map, t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->map_height = 0;
	fdf->map_width = 0;
	while (str_map[i] != '\n' && str_map[i])
	{
		while (str_map[i] == ' ')
			i++;
		if (ft_isdigit(str_map[i]) || str_map[i] == '-' || str_map[i] == '+')
			fdf->map_width++;
		while (ft_isdigit(str_map[i]) || str_map[i] == '-'
			|| str_map[i] == '+')
			i++;
		if (str_map[i] == ',')
			i += skip_hex(&str_map[i]);
	}
	while (str_map[i])
	{
		if (str_map[i] == '\n')
			fdf->map_height++;
		i++;
	}
}

void	set_map(char *str_map, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str_map[i] && j < (fdf->map_width * fdf->map_height))
	{
		while (ft_iswhitespace(str_map[i]))
			i++;
		fdf->map[j] = ft_atoi(&str_map[i]);
		i += ft_numlen(fdf->map[j]);
		if (str_map[i] == ',')
			i += skip_hex(&str_map[i]);
		j++;
	}
}

void	set_colors(char *str_map, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str_map[i] && j < (fdf->map_width * fdf->map_height))
	{
		while (ft_iswhitespace(str_map[i]))
			i++;
		while (ft_isdigit(str_map[i]))
			i++;
		if (str_map[i] == ',')
		{
			i++;
			fdf->map3d[j] = get_point_color(fdf->map3d[j], &str_map[i]);
			i += skip_hex(&str_map[i]);
		}
		else
		{
			fdf->map3d[j] = set_height_color(fdf->map3d[j], fdf);
		}
		j++;
	}
}

void	set_map3d(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map_width * fdf->map_height)
	{
		fdf->map3d[i].x = (i % fdf->map_width) - (fdf->map_width >> 1);
		fdf->map3d[i].y = (i / fdf->map_width) - (fdf->map_height >> 1);
		fdf->map3d[i].z = fdf->map[i];
		i++;
	}
}

void	set_maps(char *str_map, t_fdf *fdf)
{
	get_map_size(str_map, fdf);
	fdf->map = malloc(sizeof(int) * (fdf->map_width * fdf->map_height));
	fdf->map3d = malloc(sizeof(t_point3d) * (fdf->map_width * fdf->map_height));
	fdf->transformed_map = malloc(sizeof(t_point3d)
			* (fdf->map_width * fdf->map_height));
	if (fdf->map == 0 || fdf->map3d == 0
		|| fdf->transformed_map == 0)
		fdf_exit("set_maps\n", 10);
	set_map(str_map, fdf);
	set_map3d(fdf);
	get_height_extremes(fdf);
	set_colors(str_map, fdf);
}
