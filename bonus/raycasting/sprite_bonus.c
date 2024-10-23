/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradais <paradais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 01:44:30 by paradais          #+#    #+#             */
/*   Updated: 2024/10/23 05:46:02 by paradais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void load_shot_sprites(t_map_data *map)
{
	int		i;
	char	*join1;
	char	*join2;

	map->shot_sprites = malloc(sizeof(t_texture_data *) * SHOT_FRAMES);
	if (!map->shot_sprites)
		error("Memory allocation failed\n", -1, map);
	i = 0;
	while (i < SHOT_FRAMES)
	{
		join1 = ft_strjoin2("bonus/boooom/fireing/", ft_itoa(i + 1));
		if (!join1)
			error("Memory allocation failed\n", -1, map);
		join2 = ft_strjoin2(join1, ".png");
		map->shot_sprites[i] = mlx_load_png(join2);
		if (!map->shot_sprites[i])
			error("Failed to load texture\n", -1, map);
		free(join1);
		free(join2);
		i++;
	}	
}

void	load_reload_sprites(t_map_data *map)
{
	int		i;
	char	*join1;
	char	*join2;

	map->reload_sprites = malloc(sizeof(t_texture_data *) * RELOAD_FRAMES);
	if (!map->reload_sprites)
		error("Memory allocation failed\n", -1, map);
	i = 0;
	while (i < RELOAD_FRAMES)
	{
		join1 = ft_strjoin2("bonus/boooom/reloading/", ft_itoa(i + 1));
		if (!join1)
			error("Memory allocation failed\n", -1, map);
		join2 = ft_strjoin2(join1, ".png");
		map->reload_sprites[i] = mlx_load_png(join2);
		if (!map->reload_sprites[i])
			error("Failed to load texture\n", -1, map);
		free(join1);
		free(join2);
		i++;
	}
}

void	display_shot_animation(t_map_data *map, int i)
{
	static mlx_image_t	*destroy;

	if (destroy)
		mlx_delete_image(map->mlx, destroy);
	map->img2 = mlx_texture_to_image(map->mlx, map->shot_sprites[i]);
	if (!map->img2)
		error("Failed to load texture\n", -1, map);
	destroy = map->img2;
	mlx_image_to_window(map->mlx, map->img2, WIDTH / 2 - map->img2->width / 2, HEIGHT - map->img2->height);
}

void	display_realod_animation(t_map_data *map, int i)
{
	static mlx_image_t	*destroy;

	if (destroy)
		mlx_delete_image(map->mlx, destroy);
	map->img2 = mlx_texture_to_image(map->mlx, map->reload_sprites[i]);
	if (!map->img2)
		error("Failed to load texture\n", -1, map);
	destroy = map->img2;
	mlx_image_to_window(map->mlx, map->img2, WIDTH / 2 - map->img2->width / 2, HEIGHT - map->img2->height);
}

void	spirite(void *param)
{
	static int	press;
	static int	press1;
	static int	i;
	static int	j;
	mlx_texture_t	*texture;
	t_map_data	*map;

	map = (t_map_data *)param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_SPACE))
	{
		press = 1;
		i = 0;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_R))
	{
		press1 = 1;
		j = 0;
	}
	if (press)
	{
		mlx_delete_image(map->mlx, map->img2);
		display_shot_animation(map, i);
		i++;
		if (i == SHOT_FRAMES)
		{
			press = 0;
			i = 0;
		}
	}
	if (press1)
	{
		mlx_delete_image(map->mlx, map->img2);
		display_realod_animation(map, j);
		j++;
		if (j == RELOAD_FRAMES)
		{
			press1 = 0;
			j = 0;
		}
	}
}