/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 14:14:32 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 12:00:51 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <errno.h>
#include <string.h>

void	fdf_exit(const char *fname, int error)
{
	if (error == 1)
		ft_printf("Error: Invalid Filepath: %s. %s\n", strerror(errno), fname);
	else if (error == 2)
		ft_printf("Error: File reading failed: %s. %s\n",
			strerror(errno), fname);
	else if (error == 3)
		ft_printf("Error: String allocation failed: %s. %s\n",
			strerror(errno), fname);
	else if (error == 4)
		ft_printf("Error: No argument given. %s\n", fname);
	else if (error == 5)
		ft_printf("Error: Not a '.fdf' file. %s\n", fname);
	else if (error == 6)
		ft_printf("Error: Too many arguments. %s\n", fname);
	else if (error == 7)
		ft_printf("Error: MLX failed to initialize.\n %s", fname);
	else if (error == 8)
		ft_printf("Error: MLX failed to create image.\n %s", fname);
	else if (error == 9)
		ft_printf("Error: MLX failed to put image to window.\n %s", fname);
	else if (error == 10)
		ft_printf("Error: Map allocation Failed.\n %s", fname);
	exit(EXIT_SUCCESS);
}
