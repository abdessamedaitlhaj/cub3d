/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:25:11 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:11:29 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_scene(t_map_data *map)
{
	map->collected_data = NULL;
	map->map = NULL;
	map->map_height = 0;
	map->elements = 0;
	map->count_colors = 2;
	map->count_textures = 4;
	map->player = ft_malloc(sizeof(t_player_data), &map->collected_data);
	map->texture = ft_malloc(sizeof(t_texture_data), &map->collected_data);
	map->fd = 0;
	map->max_width = 0;
	map->count_directions = 0;
	map->texture->texture_n = NULL;
	map->texture->texture_s = NULL;
	map->texture->texture_w = NULL;
	map->texture->texture_e = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->comp1 = NULL;
	map->comp2 = NULL;
	map->player_x = 0;
	map->player_y = 0;
}

// void	print_matrix(t_map_data *map)
// {
// 	int i, j;

// 	i = 0;
// 	while (i < map->map_height)
// 	{
// 		j = 0;
// 		while (map->map[i][j])
// 		{
// 			write(1, &map->map[i][j], 1);
// 			j++;
// 		}
// 		write(1, "\n", 1);
// 		i++;
// 	}
// }

void f()
{
	system("leaks cub3D");
}

int	main (int argc, char **argv) 
{
	t_map_data map;

	atexit(f);
	if (argc != 2)
	{
		write (2, "Error\n", 6);
		write (2, "Usage: ./cub3d map.cub\n", 22);
		return (1);
	}
	init_scene(&map);
	check_file_extention(argv[1], &map);
	load_file(argv[1], &map);
	fill_matrix(argv[1], &map);
	//raycasting_scene(&map);
	//free_data(&map);
	printf("done\n");
	return (0);
}
