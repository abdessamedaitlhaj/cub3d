/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:37:03 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/27 18:11:10 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	store_texture(char *type, char *path, t_map_data *map)
{
	if (ft_strncmp(type, "NO", 2) == 0)
		map->texture->north = ft_strdup(path);
	if (ft_strncmp(type, "SO", 2) == 0)
		map->texture->south = ft_strdup(path);
	if (ft_strncmp(type, "WE", 2) == 0)
		map->texture->weast = ft_strdup(path);
	if (ft_strncmp(type, "EA", 2) == 0)
		map->texture->east = ft_strdup(path);
}

