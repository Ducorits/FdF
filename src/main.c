/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:44:57 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/15 14:00:45 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "ft_printf.h"
#include "libft.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2)
	{
		ft_printf("Argument was given.\n Now what?\n");
	}
	else
		ft_printf("No argument given.\n");
	return (0);
}
