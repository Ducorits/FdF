/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:50:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/20 18:15:21 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

void	free_2d_array(void **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	**parse_line(char *to_parse)
{
	int		i;
	char	**first_split;
	char	***second_split;

	first_split = ft_split(to_parse, '\n');
	if (!first_split)
		return (0);
	i = 0;
	while (first_split[i])
		i++;
	second_split = malloc(i + 1 * sizeof(char *));
	i = 0;
	while (first_split[i])
	{
		second_split[i] = ft_split(first_split[i], ' ');
		ft_printf("%s\n", second_split[i][0]);
		i++;
	}
	free_2d_array((void *)first_split);
	return (0);
}

void	parse_map(char *file_name, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	*to_parse;

	fd = open(file_name, O_RDONLY);
	to_parse = malloc(1);
	*to_parse = 0;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			to_parse = ft_strjoin_free(to_parse, line);
			free(line);
		}
	}
	fdf->map = parse_line(to_parse);
	free(to_parse);
	close(fd);
	fdf = fdf + 1;
}

int	check_errors(char *file_name)
{
	int	i;
	int	len;

	len = ft_strlen(file_name);
	if (len < 4)
		return (1);
	i = len - 4;
	if (ft_strncmp(&file_name[i], ".fdf", 4))
		return (1);
	return (0);
}
