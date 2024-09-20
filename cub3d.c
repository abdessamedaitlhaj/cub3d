/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:25:11 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/20 14:42:30 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char	*message)
{
	write (2, "Error\n", 6);
	write (2, message, ft_strlen(message));
	exit(1);
}

void	check_file_extention(char *file)
{
	int i;

	i = ft_strlen(file);
	if (i >= 4 && (file[i - 1] != 'b' || file[i - 2] != 'u' || \
	file[i - 3] != 'c' || file[i - 4] != '.'))
		error("Invalid file extension\n");
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

void	element_type(char *line, t_map_data *map)
{
	char	**comp;

	comp = ft_split(line, ' ');
	if (!comp)
		error("Memory allocation failed\n");
	if (ft_strlen(comp[0]) == 1)
	{
		if (comp[0][0] != 'F' && comp[0][0] != 'C')
			error("Color character is invalid\n");
		if (count_strings(comp) != 2)
			error("Color format is invalid\n");
		map->elements++;
	}
	else if (ft_strlen(comp[0]) == 2)
	{
		if (ft_strncmp(comp[0], "NO", 2) && ft_strncmp(comp[0], "SO", 2) && \
		ft_strncmp(comp[0], "WE", 2) && ft_strncmp(comp[0], "EA", 2))
			error("Texture symboles are invalid\n");
		map->elements++;
	}
	if (map->elements > 6)
		error("Too many elements\n");
}

void	load_file(char *file, t_map_data *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Can't open the file\n");
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		element_type(line, map);
		free(line);
		line = get_next_line(fd);
	}
}

void	init_scene(t_map_data *map)
{
	map->map = NULL;
	map->map_width = 0;
	map->map_height = 0;
	map->elements = 0;
	map->player = malloc(sizeof(t_player_data));
	if (!map->player)
		error("Memory allocation failed\n");
	map->texture = malloc(sizeof(t_texture_data));
	if (!map->texture)
		error("Memory allocation failed\n");
	map->texture->count = 0;
	map->texture->north = NULL;
	map->texture->south = NULL;
	map->texture->weast = NULL;
	map->texture->east = NULL;
	map->texture->floor = NULL;
	map->texture->ceiling = NULL;
}

int	main (int argc, char **argv) 
{
	t_map_data map;

	if (argc != 2)
	{
		write (2, "Error\n", 6);
		write (2, "Usage: ./cub3d map.cub\n", 22);
		return (1);
	}
	init_scene(&map);
	check_file_extention(argv[1]);
	load_file(argv[1], &map);
	// load_data(argv[1], &map);
	//execute_scene()
	return (0);
}