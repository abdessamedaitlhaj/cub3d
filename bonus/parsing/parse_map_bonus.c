/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:25 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 20:10:29 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	check_directions(t_map_data *map, char c, int j)
{
	int	flag;

	if (c == 'N')
		map->count_directions++;
	if (c == 'S')
		map->count_directions++;
	if (c == 'W')
		map->count_directions++;
	if (c == 'E')
		map->count_directions++;
	if (map->count_directions > 1)
		error("Multiple player directions\n", map->fd, map);
	if (j == -1 && !map->count_directions)
		error("No player direction\n", map->fd, map);
}

void	save_player_position(t_map_data *map, char *line, size_t i, int j)
{
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
	{
		map->player_x = i;
		map->player_y = j;
	}
}

void	check_map_matrix(t_map_data *map, char *line, int j)
{
	size_t	i;

	if (j != -1)
		map->map_height++;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '1')
		error("Map is not surrounded by walls\n", map->fd, map);
	while (line[i])
	{
		if (j == map->map_height)
			check_wall(line, map);
		if (j == 0)
			check_wall(line, map);
		if (line[i] != '0' && line[i] != '1' && \
		line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && \
		!ft_isspace(line[i]))
			error("Invalid map character\n", map->fd, map);
		check_directions(map, line[i], j);
		save_player_position(map, line, i, j);
		i++;
		last_char_check(map, line, i);
	}
}

void	check_map(t_map_data *map, char *line)
{
	char	*last_line;
	size_t	i;

	i = 0;
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			error("Empty line in the map\n", map->fd, map);
			break ;
		}
		check_map_matrix(map, line, i);
		last_line = ft_strdup(line);
		free(line);
		line = get_next_line(map->fd);
		if (!line)
			check_map_matrix(map, last_line, -1);
		free(last_line);
		i++;
	}
}

void	load_file(char *file, t_map_data *map)
{
	char	*line;
	char	*last_line;
	size_t	i;

	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
		error("Can't open the file\n", -1, map);
	line = get_next_line(map->fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(map->fd);
			continue ;
		}
		if (element_type(line, map))
			break ;
		free(line);
		line = get_next_line(map->fd);
	}
	if (!line)
		error("Missing data\n", map->fd, map);
	check_map(map, line);
	close(map->fd);
}
