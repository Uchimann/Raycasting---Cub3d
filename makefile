CC = gcc
FLAGS = -Wall -Wextra -Werror -g
NAME = cub3d
SRCS = maps/*.c libft/*.c

all: $(NAME)
$(NAME):
	make -C ./minilibx-linux && mv ./minilibx-linux/libmlx.a .
	$(CC) $(SRCS) -o $(NAME) libmlx.a -lXext -lX11 -lm 
clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re