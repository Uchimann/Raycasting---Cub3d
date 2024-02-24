CC = gcc
FLAGS = -Wall -Wextra -Werror -g
NAME = cub3d
SRCS = maps/*.c libft/*.c

all: $(NAME)
$(NAME):
	make -C ./minilibx && mv ./minilibx/libmlx.a .
	$(CC) $(SRCS) -o $(NAME) libmlx.a -framework OpenGL -framework AppKit -lm
clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re