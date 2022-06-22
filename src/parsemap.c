/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:50:16 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/22 15:13:26 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

void	fill_map(t_fdf *fdf, char ***parsed_strings)
{
	int	i;
	int	j;
	int	line_size;

	i = ft_2darlen((void **)parsed_strings);
	fdf->map = malloc(sizeof(int *) * i + 1);
	i = 0;
	line_size = 0;
	while (parsed_strings[i])
	{
		line_size = ft_2darlen((void **)parsed_strings[i]);
		fdf->map[i] = malloc(sizeof(int) * line_size);
		i++;
	}
	fdf->map[i] = 0;
	i = 0;
	while (parsed_strings[i])
	{
		j = 0;
		while (parsed_strings[i][j])
		{
			fdf->map[i][j] = ft_atoi(parsed_strings[i][j]);
			j++;
		}
		fdf->map[i][j] = 0;
		i++;
	}
	print_map(fdf);
}

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

int	**parse_line(char *to_parse, t_fdf *fdf)
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
	second_split = malloc((i + 1) * sizeof(char *));
	if (!second_split)
		return (0);
	second_split[i] = 0;
	i = 0;
	while (first_split[i])
	{
		second_split[i] = ft_split(first_split[i], ' ');
		i++;
	}
	fill_map(fdf, second_split);
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
	parse_line(to_parse, fdf);
	free(to_parse);
	close(fd);
	fdf = fdf + 1;
}
