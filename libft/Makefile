CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=libft.a
SRCS=ft_printf.c ft_put1.c ft_put2.c get_next_line.c get_next_line_utils.c ft_split.c ft_itoa.c ft_atoi.c
OBJS=$(SRCS:.c=.o)
HEADER=-I../header/

all: $(NAME)

%.o: %.c
	$(CC) $(HEADER) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all