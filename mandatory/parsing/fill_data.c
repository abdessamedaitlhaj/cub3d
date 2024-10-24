/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:56:43 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:11:02 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_open_spaces(t_map_data *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->map_height)
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == '0')
			{
				if (j > get_map_width(map->map[i - 1]) - 1 || \
				(i + 1 < map->map_height && \
				j > get_map_width(map->map[i + 1]) - 1))
					error("Open space\n", -1, map);
			}
			if (ft_isspace(map->map[i][j]))
			{
				if (map->map[i][j + 1] == '0' || map->map[i][j - 1] == '0' || \
				(i + 1 < map->map_height && map->map[i + 1][j] == '0') || \
				(i - 1 >= 0 && map->map[i - 1][j] == '0'))
					error("Open space\n", -1, map);
			}
		}
	}
}

char	*skip_elements(t_map_data *map)
{
	char	*line;
	int		j;

	line = get_next_line(map->fd, &map->collected_data);
	j = 0;
	while (line && j < 6)
	{
		if (is_empty_line(line))
		{
			line = get_next_line(map->fd, &map->collected_data);
			continue ;
		}
		line = get_next_line(map->fd, &map->collected_data);
		j++;
	}
	while (is_empty_line(line))
		line = get_next_line(map->fd, &map->collected_data);
	return (line);
}

void	fill_map(t_map_data *map, char *line)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	m;

	i = -1;
	while (++i < map->map_height)
	{
		l = get_map_width(line);
		map->map[i] = ft_malloc(l + 1, &map->collected_data);
		j = 0;
		k = 0;
		while (ft_isspace(line[j]))
			j++;
		m = j;
		while (line[j] && j < m + l)
			map->map[i][k++] = line[j++];
		map->map[i][k] = '\0';
		line = get_next_line(map->fd, &map->collected_data);
	}
}

void	fill_matrix(char *file, t_map_data *map)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	map->map = ft_malloc(sizeof(char *) * \
	(map->map_height), &map->collected_data);
	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
		error("Can't open the file\n", -1, map);
	line = skip_elements(map);
	fill_map(map, line);
	check_open_spaces(map);
	close(map->fd);
}
