SRCS =	 main.c parse_file.c math.c
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = 
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)
PRINTF_SRCS = ft_printf/ft_printf.c ft_printf/ft_itoh.c ft_printf/ft_itohi.c ft_printf/ft_uitoa.c ft_printf/ft_helper0.c ft_printf/ft_helper1.c ft_printf/ft_helper2.c
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)
CC = cc
AR = ar
C_FLAGS = -Wall -Wextra -Werror -Ofast# -O3 -g -fsanitize=address
LD_FLAGS := -L./libft -lft -L./mlx -lmlx  -framework OpenGL -framework AppKit 
NAME = fdf
LD_FLAGS_OBJ = 
.PHONY: clean

all: $(NAME)


clean:
	cd libft && make fclean
	cd mlx/ && make clean
	rm -rf $(OBJS)  $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) debug

fclean: clean
	rm -rf $(NAME)

re: fclean all


%.o: %.c fdf.h
	$(CC) $(C_FLAGS) -c -o $@ $< $(LD_FLAGS_OBJ)

$(NAME):  libft/libft.a mlx/libmlx.a $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -o  $@ $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(LD_FLAGS) 

libft/libft.a:
	cd libft && make fclean all

mlx/libmlx.a:
	cd mlx/ && make clean all

debug: C_FLAGS+= -g
debug: LD_FLAGS+= -fsanitize=address
debug: LD_FLAGS_OBJ+= -fsanitize=address
debug:  libft/libft.a mlx/libmlx.a $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -o $@ $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(LD_FLAGS)

