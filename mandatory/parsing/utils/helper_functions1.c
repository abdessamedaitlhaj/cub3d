/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:49:52 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/24 20:05:54 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2, t_node **collected_data)
{
	char	*s;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (s1 = NULL, NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s = ft_malloc(s1_len + s2_len + 1, collected_data);
	ft_strlcpy(s, s1, s1_len + s2_len + 1);
	ft_strlcpy(s + s1_len, s2, s1_len + s2_len + 1);
	return (s);
}

char	*ft_strdup(char *s1, t_node **collected_data)
{
	int		len;
	int		i;
	char	*s2;

	len = ft_strlen(s1);
	s2 = ft_malloc(len + 1, collected_data);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_atoi(char *number, t_map_data *map)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (ft_isdigit(number[i]))
	{
		nbr = nbr * 10 + number[i] - '0';
		i++;
	}
	if (number[i] || nbr < 0 || nbr > 255)
		error("Invalid number\n", -1, map);
	return (nbr);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
