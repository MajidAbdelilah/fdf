SRCS =	ft_printf.c ft_itoh.c ft_itohi.c ft_uitoa.c ft_helper0.c ft_helper1.c ft_helper2.c 
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = 
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
gnl_SRCS = 
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
CC = cc
AR = ar
C_FLAGS = -Wall -Wextra -Werror# -O3 -g -fsanitize=address
LD_FLAGS := -L./libft -lft
NAME = libftprintf.a
#.PHONY: all clean fclean re

all: $(NAME)


clean:
	cd libft && make fclean
	rm -rf $(OBJS)  $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all


%.o: %.c
	$(CC) $(C_FLAGS) -c -o $@ $<

$(NAME):  libft/libft.a $(OBJS) $(LIBFT_OBJS)
	$(CC) $(C_FLAGS) -o $@ $(OBJS) -L./ -lft 

libft/libft.a:
	cd libft && make fclean all

debug:  libft/libft.a $(OBJS) $(LIBFT_OBJS)
	$(CC) $(C_FLAGS) -g -o $@ $(OBJS) $(LIBFT_OBJS) -fsanitize=address
