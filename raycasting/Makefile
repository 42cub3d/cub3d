CC=cc
CFLAGS=-Wall -Wextra -Werror
LMLX=-L./minilibx -lmlx -framework OpenGL -framework AppKit
NAME=raycasting
SRCS=./src/raycasting.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LMLX) \
	$(SRCS) -o $(NAME)

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all