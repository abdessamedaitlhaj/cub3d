#include "../include/cub3d.h"

int horizontal_intersection(t_map_data *map, int x, int y, double angle, int color)
{
	static int i = 50;
	i += 10;
	return (i);
}

// int vertical_intersection(t_map_data *map, int x, int y, double angle, int color)
// {
// 	;
// }

void min_intersection (t_map_data *map, int x, int y, double angle, int color)
{
	// color always red
	double distance;
	map->player->distance = horizontal_intersection(map, x, y, angle, color);
	// printf("vertical   distance = %f\n", map->player->distance);
	// distance = horizontal_intersection(map, x, y, angle, color);
	// printf("horizontal   distance = %f\n", distance);
	// if (map->player->distance > distance)
	// 	map->player->distance = distance;
}
void draw_ray(t_map_data *map, int x, int y, int color)
{
	
	int i;
	i = 0;

	double angle =  map->player->player_angle - ((FOV / 2) * (PI / 180));
	while (i < WIDTH)
	{
		min_intersection(map, x, y, angle, color);
		map->player->distance = 60;
		// printf ("point to reach x = %f, y = %f\n", x + map->player->distance * cos(angle), y + map->player->distance * sin(angle));
		put_line(map->img, x, y, x + map->player->distance * cos(angle), y + map->player->distance * sin(angle), color);

		// put_line(map->img, x, y, x + distance * cos(map->player->player_angle), y + distance * sin(map->player->player_angle), color);
		angle += map->player->ray_distance;
		printf("angle = %f\n", angle);
		printf("ray_distance = %f\n", map->player->ray_distance);

		i++;
	}
}