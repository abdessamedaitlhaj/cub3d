#include "../include/cub3d.h"

int vertical_intersection(t_map_data *map, int x, int y, double angle, int color)
{
	int facing_down = angle > 0 && angle < PI;
	int facing_right = angle < 0.5 * PI || angle > 1.5 * PI;
	int facing_left = !facing_right;
	int facing_up = !facing_down;
	double ax = floor(x / GRID_SIZE) * GRID_SIZE;
	if (facing_right)
		ax += GRID_SIZE;
	else
		ax -= 0.0001;
	double ay = y + (ax - x) * tan(angle);
	double dx = facing_right ? GRID_SIZE : -GRID_SIZE;
	double dy = dx * tan(angle);
	if (facing_up && facing_left)
		if (angle == 0 || angle == PI)
			return (map->map_height * GRID_SIZE);
		while (ax >= 0 && ax < WIDTH && ay >= 0 && ay < HEIGHT)
	{
		int map_x = (int)(ax / GRID_SIZE);
		int map_y = (int)(ay / GRID_SIZE);
		if (map_x >= 0 && map_x < map->max_width && map_y >= 0 && map_y < map->map_height) {
			if (map->map[map_y][map_x] &&   map->map[map_y][map_x] == '1')
			{
				// put_line(map->img, x, y, ax, ay, color);
				return (sqrt(pow(ax - x, 2) + pow(ay - y, 2)));
			}
		}
		ax += dx;
		ay += dy;
	}
}

int horizontal_intersection(t_map_data *map, int x, int y, double angle, int color) {
    // Normalize angle to be between 0 and 2*PI
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;

    // If angle is exactly 0 or PI, ray is horizontal and won't hit horizontal lines
    if (fabs(angle - 0) < 0.0001 || fabs(angle - PI) < 0.0001)
        return (map->map_height * GRID_SIZE);

    int facing_down = angle > 0 && angle < PI;
    int facing_right = angle < 0.5 * PI || angle > 1.5 * PI;

    // Find first horizontal intersection
    double ay = floor(y / (double)GRID_SIZE) * GRID_SIZE;
    if (facing_down)
        ay += GRID_SIZE;

    // Prevent division by zero when angle is near vertical
    double tan_angle = tan(angle);
    if (fabs(tan_angle) < 0.0001)
        return (map->map_height * GRID_SIZE);

    // Calculate x coordinate of first intersection
    double ax = x + (ay - y) / tan_angle;

    // Calculate step sizes
    double dy = facing_down ? GRID_SIZE : -GRID_SIZE;
    double dx = GRID_SIZE / tan_angle;
    if (!facing_down)
        dx = -dx;

    // Move slightly inside the grid cell to prevent edge cases
    const double EPSILON = 0.001;
    
    while (ax >= 0 && ax < WIDTH && ay >= 0 && ay < HEIGHT) {
        // Calculate the grid cell to check
        int map_x = (int)(ax / GRID_SIZE);
        // When checking upward, we need to check the cell above
        int map_y = facing_down ? (int)(ay / GRID_SIZE) : (int)(ay / GRID_SIZE) - 1;

        // Check if we're in bounds and hit a wall
        if (map_x >= 0 && map_x < map->max_width && 
            map_y >= 0 && map_y < map->map_height) {
            if (map->map[map_y][map_x] == '1') {
                // Calculate and return the distance
                double distance = sqrt(pow(ax - x, 2) + pow(ay - y, 2));
                return (distance);
            }
        }

        // Move to next intersection point
        ax += dx;
        ay += dy;
    }

    return (map->map_height * GRID_SIZE);
}



void min_intersection (t_map_data *map, int x, int y, double angle, int color)
{
	// color always red
	double distance;
	map->player->distance = horizontal_intersection(map, x, y, angle, color);

	distance = vertical_intersection(map, x, y, angle, color);

	if (map->player->distance > distance)
		map->player->distance = distance;
}
void draw_ray(t_map_data *map, int x, int y, int color)
{
	printf("hello\n");
	int i;
	i = 0;
	double angle =  map->player->player_angle - ((FOV / 2) * (PI / 180));
	angle = angle < 0 ? 2 * PI + angle : angle;
	angle = angle > 2 * PI ? angle - 2 * PI : angle;
	printf("angle = %f\n", angle);
	while (i < WIDTH)
	{
		min_intersection(map, x, y, angle, color);
		// map->player->distance = 60;
		put_line(map->img, x, y, x + map->player->distance * cos(angle), y + map->player->distance * sin(angle));
		angle += map->player->ray_distance;
		i++;
	}
}