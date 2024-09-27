SRCS = cub3d.c get_next_line.c helper_functions.c ft_split.c store_data.c utils1.c parsing.c

OBJS = $(SRCS:.c=.o)

CC = cc

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re