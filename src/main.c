/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:44:57 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/19 16:59:28 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void at_exit(void) // away with this
{
	system("leaks fdf");
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	atexit(at_exit); // away with this
	if (argc > 2)
		fdf_exit("main", 6);
	else if (argc < 2)
		fdf_exit("main", 4);
	else
	{
		error_check(argv[1]);
		fdf = fdf_init(argv[1]);
		fdf_loop(&fdf);
		fdf_free(&fdf);
	}
	return (0);
}
