/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/21 14:36:07 by dritsema      #+#    #+#                 */
/*   Updated: 2022/08/22 12:00:59 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	error_check(char *file_name)
{
	int	i;
	int	len;

	len = ft_strlen(file_name);
	if (len < 4)
		fdf_exit("(in error_check)", 5);
	i = len - 4;
	if (ft_strncmp(&file_name[i], ".fdf", 4))
		fdf_exit("(in error_check)", 5);
	return (0);
}
