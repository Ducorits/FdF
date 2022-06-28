/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:41:06 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/28 17:07:37 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_fdf
{
	int	*map;
	int	map_width;
	int	map_height;
}	t_fdf;
int		parse_map(char *file_name, t_fdf *fdf);
int		error_check(char *file_name);
void	error_message(int id);

// for debug
void	print_map(t_fdf *fdf);

#endif // FDF_H
