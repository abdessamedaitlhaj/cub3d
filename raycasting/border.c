#include "../include/cub3d.h"


int  border (t_map_data *map, int border_x , int border_y)
{
	if (map != NULL && map->player != NULL) {
    int index_y = (int)((map->player->po_y + border_y) / GRID_SIZE);
    int index_x = (int)((map->player->po_x + border_x) / GRID_SIZE);
    if (index_y >= 0 && index_y < map->map_height && index_x >= 0 && index_x < map->max_width) {
        if (map->map[index_y][index_x] == '1') {
           return(1);
        }
	}
	}
	return(0);
}
int ft_border(t_map_data *map)
{
	if (border(map , PLAYER_SIZE / 2, PLAYER_SIZE / 2) || border(map , -PLAYER_SIZE / 2, PLAYER_SIZE / 2)
		|| border(map , PLAYER_SIZE / 2, -PLAYER_SIZE / 2) || border(map , -PLAYER_SIZE / 2, -PLAYER_SIZE / 2))
		return (1);
	return (0);
}