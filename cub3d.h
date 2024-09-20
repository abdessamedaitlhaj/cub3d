/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:15:21 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/20 14:42:23 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

typedef struct s_player_data
{
	double po_x;
	double po_y;
	double dir_x;
	double dir_y;
} t_player_data;

typedef struct s_texture_data
{
	int		count;
	char	*north;
	char	*south;
	char	*weast;
	char	*east;
	char	*floor;
	char	*ceiling;
} t_texture_data;

typedef struct s_map_data
{
	char			**map;
	int				map_width;
	int				map_height;
	int				elements;
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



#endif