/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:25 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/27 18:11:23 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_color_format(char *format, t_map_data *map, char type)
{
	char	*format_trim;
	char	**comp;

	format_trim = ft_strtrim(format, "()");
	if (!format_trim)
		error("Memory allocation failed\n", map->fd);
	comp = ft_split(format_trim, ',');
	if (!comp)
	{
		free(format_trim);
		error("Memory allocation failed\n", map->fd);
	}
	if (type == 'F')
	{
		map->floor = malloc(sizeof(t_color_data));
		if (!map->floor)
		{
			free(format_trim);
			free(comp);
			error("Memory allocation failed\n", map->fd);
		}
		map->floor->red = ft_atoi(comp[0]);
		map->floor->green = ft_atoi(comp[1]);
		map->floor->blue = ft_atoi(comp[2]);
	}
	if (type == 'C')
	{
		map->ceiling = malloc(sizeof(t_color_data));
		if (!map->ceiling)
		{
			free(format_trim);
			free(comp);
			error("Memory allocation failed\n", map->fd);
		}
		map->ceiling->red = ft_atoi(comp[0]);
		map->ceiling->green = ft_atoi(comp[1]);
		map->ceiling->blue = ft_atoi(comp[2]);
	}
	
}

void	element_type(char *line, t_map_data *map)
{
	char	**comp;

	comp = ft_split(line, ' ');
	if (!comp)
		error("Memory allocation failed\n", map->fd);
	if (count_strings(comp) != 2 && map->elements < 6)
		error("Color or texture path format is invalid\n", map->fd);
	if (ft_strlen(comp[0]) == 1)
	{
		if (comp[0][0] != 'F' && comp[0][0] != 'C')
			error("Color character is invalid\n", map->fd);
		if (comp[0][0] == 'F')
			check_color_format(comp[1], map, 'F');
		if (comp[0][0] == 'C')
			check_color_format(comp[1], map, 'C');
		map->elements++;
	}
	else if (ft_strlen(comp[0]) == 2)
	{
		if (ft_strncmp(comp[0], "NO", 2) && ft_strncmp(comp[0], "SO", 2) && \
		ft_strncmp(comp[0], "WE", 2) && ft_strncmp(comp[0], "EA", 2))
			error("Texture symboles are invalid\n", map->fd);
		if (ft_strncmp(comp[0], "NO", 2) == 0)
			store_texture(comp[0], comp[1], map);
		if (ft_strncmp(comp[0], "SO", 2) == 0)
			store_texture(comp[0], comp[1], map);
		if (ft_strncmp(comp[0], "WE", 2) == 0)
			store_texture(comp[0], comp[1], map);
		if (ft_strncmp(comp[0], "EA", 2) == 0)
			store_texture(comp[0], comp[1], map);
		map->elements++;
	}
}

void	check_wall(char *line, t_map_data *map)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			error("Map is not surrounded by walls\n", map->fd);
		i++;
	}
}

void	check_map_matrix(t_map_data *map, char *line, int j)
{
	size_t	i;

	if (j != -1)
		map->map_height++;
	else
		check_wall(line, map);
	i = 0;
	while (line[i])
	{
		if (j == map->map_height)
			check_wall(line, map);
		if (j == 0)
			check_wall(line, map);
		if (i == 0)
		{
			while (line[i] == ' ')
				i++;
			if (line[i] != '1')
				error("Map is not surrounded by walls\n", map->fd);
			i = 0;
		}
		if (line[i] != '0' && line[i] != '1' && \
		line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && \
		line[i] != ' ')
			error("Invalid map character\n", map->fd);
		i++;
		if (!line[i])
		{
			i--;
			while (line[i] == ' ')
				i--;
			if (line[i] != '1')
				error("Map is not surrounded by walls\n", map->fd);
			break ;
		}
	}
}

void	load_file(char *file, t_map_data *map)
{
	char	*line;
	char	*last_line;
	size_t	i;

	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
		error("Can't open the file\n", -1);
	line = get_next_line(map->fd);
	while (line && map->elements < 6)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(map->fd);
			continue;
		}
		element_type(line, map);
		free(line);
		line = get_next_line(map->fd);
	}
	while (is_empty_line(line))
	{
		free(line);
		line = get_next_line(map->fd);
	}
	if (map->elements == 6)
	{
		i = 0;
		while (line)
		{
			if (is_empty_line(line))
			{
				free(line);
				error("Empty line in the map\n", map->fd);
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
	if (map->elements < 6)
		error("Missing elements\n", map->fd);
	close(map->fd);
}