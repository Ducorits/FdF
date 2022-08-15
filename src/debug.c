/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 15:00:47 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/15 20:26:07 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

void	error_message(int id)
{
	if (id == -1)
		ft_printf("Error!\n - Invalid Filepath.\n");
	else if (id == -2)
		ft_printf("Error!\n - File reading failed.\n");
	else if (id == -2)
		ft_printf("Error!\n - String allocation failed.\n");
	else if (id == -3)
		ft_printf("Error!\n - Not a '.fdf' file.\n");
	else if (id == -4)
		ft_printf("No argument given. Or incorrect argument count\n");
}
