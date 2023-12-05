SRCS =	 main.c
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = 
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)
PRINTF_SRCS = ft_printf/ft_printf.c ft_printf/ft_itoh.c ft_printf/ft_itohi.c ft_printf/ft_uitoa.c ft_printf/ft_helper0.c ft_printf/ft_helper1.c ft_printf/ft_helper2.c
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)
CC = cc
AR = ar
C_FLAGS = -Wall -Wextra -Werror# -O3 -g -fsanitize=address
LD_FLAGS := -L./libft -lft
NAME = libftprintf.a
#.PHONY: all clean fclean re

all: $(NAME)


clean:
	cd libft && make fclean
	rm -rf $(OBJS)  $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS) 

fclean: clean
	rm -rf $(NAME)

re: fclean all


%.o: %.c
	$(CC) $(C_FLAGS) -c -o $@ $<

$(NAME):  libft/libft.a $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -o  $@ $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) -L./libft/ -lft 

libft/libft.a:
	cd libft && make fclean all

debug:  libft/libft.a $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(C_FLAGS) -g -o $@ $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) -fsanitize=address
