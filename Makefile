NAME = so_long

CFLAGS = -Wall -Wextra -Werror -I ./Users/$(USER)/Desktop/so_long-42/MLX42/include/MLX42/MLX42.h 

SRCS = so_long.c get_next_line.c get_next_line_utils.c prcingmap.c mapvrf.c \
        mapcheck.c graphic.c graphcheck.c  map_prc.c prchmap.c

MLX = /Users/$(USER)/Desktop/so_long-42/MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -L /goinfre/yobourai/homebrew/opt/glfw/lib
INCLUDE = so_long.h

OBJS = $(SRCS:.c=.o)

all: $(NAME) $(INCLUDE) 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re