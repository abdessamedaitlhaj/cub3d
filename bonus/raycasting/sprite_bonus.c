/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:47:31 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 23:34:56 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	display_shot_animation(t_map_data *map, int i)
{
	static mlx_image_t	*destroy;

	if (destroy)
		mlx_delete_image(map->mlx, destroy);
	map->img2 = mlx_texture_to_image(map->mlx, map->shot_sprites[i]);
	if (!map->img2)
		error("Failed to load texture\n", -1, map);
	destroy = map->img2;
	mlx_image_to_window(map->mlx, map->img2, \
	WIDTH / 2 - map->img2->width / 2, HEIGHT - map->img2->height);
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
	mlx_image_to_window(map->mlx, map->img2, \
	WIDTH / 2 - map->img2->width / 2, HEIGHT - map->img2->height);
}

void	check_shot_animation(t_map_data *map, int *press, int *i)
{
	if (*press)
	{
		mlx_delete_image(map->mlx, map->img2);
		display_shot_animation(map, *i);
		*i += 1;
		if (*i == SHOT_FRAMES)
		{
			*press = 0;
			*i = 0;
		}
	}
}

void	check_reload_animation(t_map_data *map, int *press1, int *j)
{
	if (*press1)
	{
		mlx_delete_image(map->mlx, map->img2);
		display_realod_animation(map, *j);
		*j += 2;
		if (*j >= RELOAD_FRAMES)
		{
			*press1 = 0;
			*j = 0;
		}
	}
}

void	spirite(void *param)
{
	static int	press;
	static int	press1;
	static int	i;
	static int	j;
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
	check_shot_animation(map, &press, &i);
	check_reload_animation(map, &press1, &j);
}
