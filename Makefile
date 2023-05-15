CC=cc
CFLAGS=-Wall -Wextra -Werror
LMLX=-L./minilibx -lmlx -framework OpenGL -framework AppKit
LIBFT=./libft/libft.a
HEADER=-I./header
NAME=cub3d
SRCS=./src/main.c\
		./src/str_utils.c\
		./src/key_hook.c\
		./src/draw_map.c\
		./src/map_parsing_init.c\
		./src/cub3d_utils.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(HEADER) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(HEADER) $(CFLAGS) $(LIBFT) $(LMLX) \
	$(SRCS) -o $(NAME)

$(LIBFT):
	make -C ./libft

.PHONY: clean fclean re all

clean:
	make -C ./libft fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all