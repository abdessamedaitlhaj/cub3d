/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:25:11 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/29 18:06:45 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"


void	init_scene(t_map_data *map)
{
	map->map = NULL;
	map->map_height = 0;
	map->elements = 0;
	map->count_colors = 2;
	map->count_textures = 4;
	map->player = malloc(sizeof(t_player_data));
	if (!map->player)
		error("Memory allocation failed\n", -1);
	map->texture = malloc(sizeof(t_texture_data));
	if (!map->texture)
		error("Memory allocation failed\n", -1);
	map->fd = 0;
	map->texture->north = NULL;
	map->texture->south = NULL;
	map->texture->weast = NULL;
	map->texture->east = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
}

void	fill_matrix(char *file, t_map_data *map)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	map->map = malloc(sizeof(char *) * (map->map_height));
	if (!map->map)
		error("Memory allocation failed\n", -1);
	map->fd = open(file, O_RDONLY);
	if (map->fd < 0)
		error("Can't open the file\n", -1);
	line = get_next_line(map->fd);
	j = 0;
	while (line && j < 6)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(map->fd);
			continue;
		}
		free(line);
		line = get_next_line(map->fd);
		j++;
	}
	while (is_empty_line(line))
	{
		free(line);
		line = get_next_line(map->fd);
	}
	i = 0;
	while (i < map->map_height)
	{
		map->map[i] = malloc(get_map_width(line) + 1);
		if (!map->map[i])
			error("Memory allocation failed\n", -1);
		j = 0;
		k = 0;
		while (line[j])
		{
			if (line[j] != ' ')
				map->map[i][k++] = line[j];
			j++;
		}
		map->map[i][k] = '\0';
		i++;
		free(line);
		line = get_next_line(map->fd);
	}
	close(map->fd);
}



void	print_matrix(t_map_data *map)
{
	int i, j;


	i  =0;
	while (i < map->map_height)
	{
		j = 0;
		while (map->map[i][j])
		{
			write(1, &map->map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
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
	fill_matrix(argv[1], &map);
	print_matrix(&map);
	//raycasting_scene(&map);
	//  execute_scene();
	return (0);
}