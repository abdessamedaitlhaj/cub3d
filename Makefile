CC = cc 
FLAGS = -w #-Wall -Wextra -Werror
FLAGS += -fsanitize=address
NAME = CUB3D
RM = rm -f
SRCS = 	cub3d.c 			\
		parsing/get_next_line.c		\
 		parsing/helper_functions.c	\
  		parsing/ft_split.c			\
   		parsing/store_data.c		\
   	 	parsing/utils1.c			\
	 	parsing/parsing.c			\
		raycasting/map_init.c		\
		raycasting/raycasting.c		\
		raycasting/border.c	
		
NEW_MLX			=	"/Users/$(USER)/MLX42/build/libmlx42.a" -Iinclude -lglfw \
				-L"/Users/$(USER)/homebrew/opt/glfw/lib/"	\
				-framework Cocoa -framework OpenGL 		\
				-framework IOKit
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $(OBJS)  -o $(NAME) $(NEW_MLX)

%.o: %.c include/cub3d.h
	$(CC) $(FLAGS) -c $< -o $@ $(NEW_MLX)

clean:
	$(RM) -f $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
