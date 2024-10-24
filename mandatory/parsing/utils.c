/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:35:44 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:22:12 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	error(char	*message, int fd, t_map_data *map)
{
	write (2, "Error\n", 6);
	write (2, message, ft_strlen(message));
	if (fd > 2)
		close(fd);
	free_allocated(&map->collected_data);
	exit(1);
}

void	check_file_extention(char *file, t_map_data *map)
{
	int	i;

	i = ft_strlen(file);
	if (i < 4 && (file[i - 1] != 'b' || file[i - 2] != 'u' || \
	file[i - 3] != 'c' || file[i - 4] != '.'))
		error("Invalid file extension\n", -1, map);
}

int	is_empty_line(char *line)
{
	int	i;

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
	int	j;
	int	len;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (ft_isspace(line[i]))
		i--;
	j = 0;
	while (ft_isspace(line[j]))
		j++;
	return (i - j + 1);
}
