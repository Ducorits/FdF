/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 13:26:01 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/15 20:44:25 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
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
	set_maps(str_map, fdf);
	free(str_map);
	return (0);
}
