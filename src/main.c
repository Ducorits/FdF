/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:44:57 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/28 17:58:43 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	int		parse_ret;

	if (argc == 2)
	{
		if (error_check(argv[1]))
		{
			error_message(-3);
			return (0);
		}
		parse_ret = parse_map(argv[1], &fdf);
		if (parse_ret < 0)
		{
			error_message(parse_ret);
			return (0);
		}
		// print_map(&fdf);

		free(fdf.map);
	}
	else
		error_message(-4);
	return (0);
}
