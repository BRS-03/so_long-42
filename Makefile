NAME = so_long
CFLAGS = -Wall -Wextra -Werror -I./MLX42/include/MLX42/MLX42.h 
SRCS = so_long.c get_next_line.c get_next_line_utils.c  
MLX = ./MLX42/build/libmlx42.a  -Iinclude -ldl -lglfw -L "/Users/yobourai/.brew/opt/glfw/lib"
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o  $(NAME) $(OBJS) $(MLX)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re