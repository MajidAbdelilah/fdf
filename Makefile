SRCS =	  parse_file.c math.c utils.c window.c draw.c
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = fdf_bonus.c window_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)
PRINTF_SRCS = ft_printf/ft_printf.c ft_printf/ft_itoh.c ft_printf/ft_itohi.c ft_printf/ft_uitoa.c ft_printf/ft_helper0.c ft_printf/ft_helper1.c ft_printf/ft_helper2.c
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)
CC = cc
AR = ar
C_FLAGS = -Wall -Wextra -Werror -Ofast# -O3 -g -fsanitize=address
LD_FLAGS := -L./libft -lft -lmlx  -framework OpenGL -framework AppKit 
NAME = fdf
LD_FLAGS_OBJ = 
.PHONY: clean

all: $(NAME)


clean:
	cd libft && make fclean
	rm -rf $(OBJS)  $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) debug bonus b_debug main.o

fclean: clean
	rm -rf $(NAME)

re: fclean all


%.o: %.c fdf.h
	$(CC) $(C_FLAGS) -c -o $@ $< $(LD_FLAGS_OBJ)

$(NAME):  libft/libft.a main.o $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -o  $@ main.o $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(LD_FLAGS) 

libft/libft.a:
	cd libft && make fclean all


bonus: libft/libft.a $(OBJS) $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -o  $@ $(OBJS)  $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(LD_FLAGS) 

debug: C_FLAGS+= -g
debug: LD_FLAGS+= -fsanitize=address
debug: LD_FLAGS_OBJ+= -fsanitize=address
debug:  libft/libft.a main.o  $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -o $@ main.o $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(LD_FLAGS)


b_debug: C_FLAGS+= -g
b_debug: LD_FLAGS+= -fsanitize=address
b_debug: LD_FLAGS_OBJ+= -fsanitize=address
b_debug: libft/libft.a $(OBJS) $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -o  $@ $(OBJS)  $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(LD_FLAGS)

