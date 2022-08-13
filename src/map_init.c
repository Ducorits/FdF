/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 13:26:01 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/13 15:33:53 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	skip_hex(char *str_map)
{
	int	i;

	i = 0;
	if (*str_map == ',')
		i++;
	while (ft_isalnum(str_map[i]))
		i++;
	return (i);
}

void	get_map_size(char *str_map, t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->map_height = 0;
	fdf->map_width = 0;
	while (str_map[i] != '\n' && str_map[i] != 0)
	{
		while (ft_iswhitespace(str_map[i]))
			i++;
		if (ft_isdigit(str_map[i]) || str_map[i] == '-' || str_map[i] == '+')
		{
			while (ft_isdigit(str_map[i]) || str_map[i] == '-'
				|| str_map[i] == '+')
				i++;
			fdf->map_width++;
		}
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

void	fill_map(char *str_map, t_fdf *fdf)
{
	int	num;
	int	numlen;
	int	i;
	int	j;

	get_map_size(str_map, fdf);
	fdf->map = malloc(sizeof(int) * (fdf->map_width * fdf->map_height));
	fdf->map3d = malloc(sizeof(t_point3d) * (fdf->map_width * fdf->map_height));
	i = 0;
	j = 0;
	while (str_map[i] && j < (fdf->map_width * fdf->map_height))
	{
		num = ft_atoi(&str_map[i]);
		fdf->map[j] = num;
		fdf->map3d[j].x = (j % fdf->map_width) - (fdf->map_width / 2);
		fdf->map3d[j].y = (j / fdf->map_width) - (fdf->map_height / 2);
		fdf->map3d[j].z = num;
		numlen = ft_numlen(num);
		i += numlen;
		if (str_map[i] == ',')
		{
			i++;
			fdf->map3d[j].r = ft_hextoi(&str_map[i]);
			fdf->map3d[j].g = ft_hextoi(&str_map[i]) >> 8;
			fdf->map3d[j].b = ft_hextoi(&str_map[i]) >> 16;
			fdf->map3d[j].color = ft_hextoi(&str_map[i]);
			i += skip_hex(&str_map[i]);
		}
		else
		{
			fdf->map3d[j].r = 0xFF;
			fdf->map3d[j].g = 0xFF;
			fdf->map3d[j].b = 0xFF;
			fdf->map3d[j].color = 0xFFFFFFFF;
		}
		j++;
		while (ft_iswhitespace(str_map[i]))
			i++;
	}
}

char	*read_map(char *file_name)
{
	int		fd;
	int		read_b;
	char	buff[100001];
	char	*str_map;

	read_b = 1;
	str_map = malloc(1);
	*str_map = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		fdf_exit("(in map_init)", 1);
	while (read_b > 0)
	{
		ft_bzero(buff, 100001);
		read_b = read(fd, buff, 100000);
		if (read_b < 0)
			fdf_exit("(in map_init)", 2);
		str_map = ft_strjoin_free(str_map, buff);
		if (str_map == 0)
			fdf_exit("(in map_init)", 3);
	}
	close(fd);
	return (str_map);
}

int	map_init(char *file_name, t_fdf *fdf)
{
	char	*str_map;

	str_map = read_map(file_name);
	fill_map(str_map, fdf);
	free(str_map);
	return (0);
}
