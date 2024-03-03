NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =  ./maps/main.c ./maps/free.c	./maps/map_control.c ./maps/map_buff_read.c \
		./maps/map_control_directions_buff.c ./maps/map_control_utils.c ./maps/map_control_utils2.c \
		./maps/map_controls_directions.c ./maps/map_controls_directions2.c ./maps/real_map.c \
		./maps/utils.c ./raycast/raycast.c ./raycast/raycast2.c ./raycast/raycast3.c \
		./raycast/raycast4.c ./libft/ft_isdigit.c ./libft/ft_strlen.c ./libft/ft_strtrim.c \
		./libft/get_next_line.c ./libft/printf.c ./libft/split.c ./maps/map_control_utils3.c \
		./libft/strchr.c ./libft/strdup.c ./libft/strjoin.c ./libft/strlcpy.c \
		./libft/strncmp.c ./libft/substr.c ./libft/ft_atoi.c ./maps/map_control_directions_buff2.c
OBJS = $(SRCS:.c=.o)
RM = rm -f
MLX =./minilibx/libmlx_libmlx.a
LIBS = -L./minilibx -lmlx -framework OpenGL -framework AppKit -lm

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C minilibx
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(MLX):
	@$(MAKE) -C minilibx

clean:
	@$(MAKE) -C minilibx clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re