/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:44:57 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/20 16:34:35 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MLX42.h"
#include "libft.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2)
	{
		if (check_errors(argv[1]))
		{
			ft_printf("Not a .fdf file\n");
		}
		parse_map(argv[1], &fdf);
	}
	else
		ft_printf("No argument given. Or incorrect argument count\n");
	return (0);
}
