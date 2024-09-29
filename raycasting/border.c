#include "../include/cub3d.h"


int border (t_map_data *map, int border_x , int border_y)
{
	//reverse check if the position is inside a wall
	if (map->map[(int)((map->player->po_y + border_y) / GRID_SIZE)][(int)((map->player->po_x + border_x)/ GRID_SIZE)] == '1')
		return (1);
	return(0);
}