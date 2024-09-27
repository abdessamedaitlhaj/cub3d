/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:35:44 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/25 21:37:23 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char	*message, int fd)
{
	write (2, "Error\n", 6);
	write (2, message, ft_strlen(message));
	if (fd > 2)
		close(fd);
	exit(1);
}

void	check_file_extention(char *file)
{
	int i;

	i = ft_strlen(file);
	if (i >= 4 && (file[i - 1] != 'b' || file[i - 2] != 'u' || \
	file[i - 3] != 'c' || file[i - 4] != '.'))
		error("Invalid file extension\n", -1);
}

int	is_empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_map_width(char *line)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			width++;
		i++;
	}
	return (width);
}
