

#ifndef CUB3D_H
# define CUB3D_H

#include </Users/ael-hara/MLX42/include/MLX42/MLX42.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

typedef struct s_player_data
{
	double		po_x;
	double		po_y;
	double		player_speed;
	double		player_angle;
	double		rotation_speed;
	double		ray_distance;
	double		distance;
	double		vertical_x;
	double		vertical_y;
	double		horizontal_x;
	double		horizontal_y;
} t_player_data;

typedef struct s_color_data
{
	int	red;
	int	green;
	int	blue;
} t_color_data;

typedef struct s_texture_data
{
	char	*north;
	char	*south;
	char	*weast;
	char	*east;
} t_texture_data;

typedef struct s_map_data
{
	char			**map;
	int				count_textures;
	int				count_colors;
	int				map_height;
	int				elements;
	int				fd;
	int 			max_width;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_color_data	*floor;
	t_color_data	*ceiling;
	t_player_data	*player;
	t_texture_data	*texture;
}	t_map_data;

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	**ft_split(char const *s, char c);
int		ft_isspace(int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		count_strings(char **s);
int		ft_isdigit(int c);



char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s, char *set);

int	ft_atoi(char *number);
void	error(char	*message, int fd);
void	check_file_extention(char *file);
int	is_empty_line(char *line);
int	get_map_width(char *line);
void	store_texture(char *type, char *path, t_map_data *map);
void	check_color_format(char *format, t_map_data *map, char type);
void	element_type(char *line, t_map_data *map);
void	check_wall(char *line, t_map_data *map);
void	check_map_matrix(t_map_data *map, char *line, int j);
void	load_file(char *file, t_map_data *map);




/////////////////////////raycasting ////////////////////////


#define WIDTH 1920
#define HEIGHT 1080
#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF 
#define RED 0xFF0000FF
#define FOV 60
#define GRID_SIZE 64
#define PLAYER_SIZE 10
#define SPEED 20
#define PI 3.14159265359
#define ROTATION_SPEED 0.2

enum e_direction
{
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4
};





void raycasting_scene(t_map_data *map);
int border (t_map_data *map, int border_x , int border_y);
int ft_border(t_map_data *map);
void draw_ray(t_map_data *map, int x, int y, int color);

void map_init(t_map_data *map);
void put_line(mlx_image_t *img, int x0, int y0, int x1, int y1);
void ft_move_player(t_map_data *map, int direction);






#endif