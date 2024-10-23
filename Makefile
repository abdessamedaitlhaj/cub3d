CC = cc 
FLAGS = -w #-Wall -Wextra -Werror
FLAGS += -fsanitize=address -g
NAME = cub3d
NAME_BONUS = cub3d_bonus
RM = rm -f
SRCS = 	mandatory/src/cub3d.c						\
		mandatory/parsing/utils/get_next_line.c		\
		mandatory/parsing/free_data.c				\
 		mandatory/parsing/utils/helper_functions1.c	\
 		mandatory/parsing/utils/helper_functions2.c	\
  		mandatory/parsing/utils/ft_split.c			\
  		mandatory/parsing/utils/ft_split2.c			\
   		mandatory/parsing/store_data.c				\
   	 	mandatory/parsing/utils.c					\
	 	mandatory/parsing/parse_map.c				\
	 	mandatory/parsing/check_elements.c			\
	 	mandatory/parsing/fill_data.c				\
		mandatory/raycasting/map_init.c				\
		mandatory/raycasting/raycasting.c			\
		mandatory/raycasting/border.c				\
		mandatory/raycasting/rendring.c				\
		mandatory/raycasting/draw_ray.c				\
		mandatory/raycasting/move.c					\
		mandatory/raycasting/intersection.c			\
		mandatory/raycasting/colors.c				\
		mandatory/raycasting/draw_line.c			\
		mandatory/raycasting/ray.c

SRCS_BONUS = bonus/src/cub3d_bonus.c					\
		bonus/parsing/utils/get_next_line_bonus.c		\
		bonus/parsing/free_data_bonus.c					\
 		bonus/parsing/utils/helper_functions1_bonus.c	\
 		bonus/parsing/utils/helper_functions2_bonus.c	\
 		bonus/parsing/utils/helper_functions3_bonus.c	\
  		bonus/parsing/utils/ft_split_bonus.c			\
  		bonus/parsing/utils/ft_split2_bonus.c			\
   		bonus/parsing/store_data_bonus.c				\
   	 	bonus/parsing/utils_bonus.c						\
	 	bonus/parsing/parse_map_bonus.c					\
	 	bonus/parsing/check_elements_bonus.c			\
	 	bonus/parsing/fill_data_bonus.c					\
		bonus/raycasting/map_init_bonus.c				\
		bonus/raycasting/raycasting_bonus.c				\
		bonus/raycasting/border_bonus.c					\
		bonus/raycasting/rendring_bonus.c				\
		bonus/raycasting/draw_ray_bonus.c				\
		bonus/raycasting/move_bonus.c					\
		bonus/raycasting/intersection_bonus.c			\
		bonus/raycasting/colors_bonus.c					\
		bonus/raycasting/draw_line_bonus.c				\
		bonus/raycasting/ray_bonus.c					\
		bonus/raycasting/sprite_bonus.c
		
NEW_MLX			=	"/Users/$(USER)/MLX42/build/libmlx42.a" -Iinclude -lglfw \
				-L"/Users/$(USER)/homebrew/opt/glfw/lib/"	\
				-framework Cocoa -framework OpenGL 		\
				-framework IOKit

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $(OBJS)  -o $(NAME) $(NEW_MLX)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) $(OBJS_BONUS)  -o $(NAME_BONUS) $(NEW_MLX)

%.o: %.c mandatory/include/cub3d.h bonus/include/cub3d_bonus.h
	$(CC) $(FLAGS) -c $< -o $@ $(NEW_MLX)


clean:
	$(RM) -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
