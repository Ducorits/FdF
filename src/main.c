/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:44:57 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/19 22:42:09 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MLX42.h"
#include "libft.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
	{
		// ft_printf("Argument was given.\nNow what to do with\n%s?\n", argv[1]);
		fd = open(argv[1], O_RDONLY);
		line = (char *)1;
		while (line)
		{
			line = get_next_line(fd);
			if (line)
			{
				ft_printf("%s", line);
				free(line);
			}
		}
	}
	else
		ft_printf("No argument given. or incorrect argument count\n");
	return (0);
}
