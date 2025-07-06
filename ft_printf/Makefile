NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -c

SRCS = ft_printf.c \
	   ft_numbers.c \
	   ft_pointer.c \
	   ft_hexa.c \
	   ft_words.c \

OBJS = $(SRCS:.c=.o)

LIBC = ar rcs

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
