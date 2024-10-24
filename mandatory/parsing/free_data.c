/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:45:35 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:11:18 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	free_comp(t_map_data *map)
// {
// 	int	i;

// 	if (map->comp1)
// 	{
// 		i = 0;
// 		while (map->comp1[i])
// 		{
// 			free(map->comp1[i]);
// 			i++;
// 		}
// 		free(map->comp1);
// 		map->comp1 = NULL;
// 	}
// 	if (map->comp2)
// 	{
// 		i = 0;
// 		while (map->comp2[i])
// 		{
// 			free(map->comp2[i]);
// 			i++;
// 		}
// 		free(map->comp2);
// 		map->comp2 = NULL;
// 	}
// }

// void	free_textures(t_map_data *map)
// {
// 	if (map->texture)
// 	{
// 		if (map->texture->texture_n)
// 			free(map->texture->texture_n);
// 		if (map->texture->texture_s)
// 			free(map->texture->texture_s);
// 		if (map->texture->texture_w)
// 			free(map->texture->texture_w);
// 		if (map->texture->texture_e)
// 			free(map->texture->texture_e);
// 		free(map->texture);
// 		map->texture = NULL;
// 	}
// }

// void	free_data(t_map_data *map)
// {
// 	int	i;

// 	i = 0;
// 	while (map->map && i < map->map_height)
// 	{
// 		if (map->map[i])
// 			free(map->map[i]);
// 		i++;
// 	}
// 	if (map->map)
// 		free(map->map);
// 	if (map->player)
// 	{
// 		free(map->player);
// 		map->player = NULL;
// 	}
// 	if (map->floor)
// 	{
// 		free(map->floor);
// 		map->floor = NULL;
// 	}
// 	if (map->ceiling)
// 	{
// 		free(map->ceiling);
// 		map->ceiling = NULL;
// 	}
// 	free_textures(map);
// 	free_comp(map);
// }

void	error_and_free(char *str, t_node **garbage_collector)
{
	free_allocated(garbage_collector);
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	*ft_lstnew(void *content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_node **list, t_node *new)
{
	t_node	*last;

	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	free_allocated(t_node **garbage_collector)
{
	t_node	*tmp;

	while (*garbage_collector)
	{
		tmp = (*garbage_collector)->next;
		free((*garbage_collector)->content);
		free(*garbage_collector);
		*garbage_collector = tmp;
	}
}

void	*ft_malloc(size_t size, t_node **garbage_collector)
{
	void	*ptr;
	t_node	*new_node;

	ptr = malloc(size);
	if (!ptr)
		error_and_free("Memory allocation failed", garbage_collector);
	new_node = ft_lstnew(ptr);
	if (!new_node)
	{
		free(ptr);
		error_and_free("malloc", garbage_collector);
	}
	ft_lstadd_back(garbage_collector, new_node);
	return (ptr);
}
