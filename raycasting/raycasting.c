#include "../include/cub3d.h"

int max_width(t_map_data *map)
{
	int i;
	int max;

	i = 0;
	max = 0;
	while (i < map->map_height)
	{
		if (ft_strlen(map->map[i]) > max)
			max = ft_strlen(map->map[i]);
		i++;
	}
	return (max);
}

void raycasting_scene(t_map_data *map)
{
	
	map->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	map->max_width = max_width(map);
	map->player->player_speed = SPEED;
	map->player->ray_distance = (FOV * (PI / 180)) / WIDTH;
	map_init(map);

	mlx_loop(map->mlx);
}
