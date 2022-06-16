/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:44:57 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/16 14:26:23 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_printf("Argument was given.\nNow what to do with\n%s?\n", argv[1]);
	}
	else
		ft_printf("No argument given.\n");
	return (0);
}
