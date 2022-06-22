/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:41:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/22 15:05:04 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_fdf
{
	int	**map;
}	t_fdf;
void	parse_map(char *file_name, t_fdf *fdf);
int		error_check(char *file_name);

// for debug
void	print_map(t_fdf *fdf);

#endif // FDF_H
