/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:47:41 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/23 23:33:20 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	free_sprites(t_map_data *map, char *str1, char *str2)
{
	int	i;

	i = 0;
	while (map->shot_sprites && i < SHOT_FRAMES)
	{
		if (map->shot_sprites[i])
			mlx_delete_texture(map->shot_sprites[i]);
		i++;
	}
	free(map->shot_sprites);
	i = 0;
	while (map->reload_sprites && i < RELOAD_FRAMES)
	{
		if (map->reload_sprites[i])
			mlx_delete_texture(map->reload_sprites[i]);
		i++;
	}
	free(map->reload_sprites);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

void	free_and_exit(t_map_data *map, char *str1, char *str2)
{
	free_sprites(map, str1, str2);
	error("Memory allocation failed\n", -1, map);
}

void	load_shot_sprites(t_map_data *map)
{
	int		i;
	char	*join1;
	char	*join2;
	char	*nbr;

	map->shot_sprites = malloc(sizeof(t_texture_data *) * SHOT_FRAMES);
	if (!map->shot_sprites)
		error("Memory allocation failed\n", -1, map);
	ft_memset(map->shot_sprites, 0, sizeof(t_texture_data *) * SHOT_FRAMES);
	i = 0;
	while (i < SHOT_FRAMES)
	{
		nbr = ft_itoa(i + 1);
		if (!nbr)
			free_and_exit(map, NULL, NULL);
		join1 = ft_strjoin2("bonus/sprites/fireing/", ft_itoa(i + 1));
		if (!join1)
			free_and_exit(map, NULL, NULL);
		join2 = ft_strjoin2(join1, ".png");
		if (!join2)
			free_and_exit(map, join1, NULL);
		map->shot_sprites[i] = mlx_load_png(join2);
		if (!map->shot_sprites[i])
			free_and_exit(map, join1, join2);
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
	char	*nbr;

	map->reload_sprites = malloc(sizeof(t_texture_data *) * RELOAD_FRAMES);
	if (!map->reload_sprites)
		error("Memory allocation failed\n", -1, map);
	i = 0;
	while (i < RELOAD_FRAMES)
	{
		nbr = ft_itoa(i + 1);
		if (!nbr)
			free_and_exit(map, NULL, NULL);
		join1 = ft_strjoin2("bonus/sprites/reloading/", ft_itoa(i + 1));
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
