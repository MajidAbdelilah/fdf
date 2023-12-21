SRCS :=	ft_putnbr_fd.c	ft_putendl_fd.c		ft_putstr_fd.c		ft_putchar_fd.c		ft_striteri.c		ft_strmapi.c	ft_itoa.c	ft_strtrim.c	ft_strjoin.c	ft_substr.c		ft_strdup.c		ft_calloc.c		ft_atoi.c	ft_strnstr.c	ft_memcmp.c		ft_memchr.c		ft_strncmp.c	ft_strchr.c		ft_strrchr.c	ft_bzero.c      ft_isalnum.c    ft_isalpha.c    ft_isascii.c    ft_isdigit.c    ft_isprint.c    ft_memcpy.c     ft_memmove.c    ft_memset.c     ft_split.c      ft_strlcat.c    ft_strlcpy.c    ft_strlen.c		ft_toupper.c	ft_tolower.c
OBJS := $(SRCS:.c=.o)
BONUS_SRCS := ft_lstnew.c	ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c		ft_lstclear.c		ft_lstiter.c	ft_lstmap.c
BONUS_OBJS := $(BONUS_SRCS:.c=.o)
CC = cc
AR = ar
C_FLAGS = -Wall -Wextra -Werror -Ofast# -O3 -g -fsanitize=address
LD_FLAGS := -lm 
NAME = libft.a
.PHONY: all clean fclean re

all: $(NAME)


clean:
	rm -rf $(OBJS)  $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all


%.o: %.c
	$(CC) $(C_FLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) rc $@  $^

bonus: $(BONUS_OBJS)
	$(AR) rc libft.a  $^

#test: LD_FLAGS += -fsanitize=address
#test: C_FLAGS += -O3 -g -fsanitize=address
test: re
test:
	$(CC) $(C_FLAGS) -I./ -c -o test.o  tests/test.c
	$(CC) $(C_FLAGS) -I./ -o $@  test.o  -L./ -lft $(LD_FLAGS)
	make fclean