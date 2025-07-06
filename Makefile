# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanjkim <hanjkim@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 13:41:16 by hanjkim           #+#    #+#              #
#    Updated: 2024/09/14 14:59:03 by hanjkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER	= server
CLIENT	= client

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

CLIENT_SRCS	=	client.c
SERVER_SRCS	=	server.c

LIBFT_DIR	= libft/
PRINTF_DIR	= ft_printf/

LIBFT = $(LIBFT_DIR)libft.a
PRINTF = $(PRINTF_DIR)libftprintf.a

CLIENT_OBJS	= ${CLIENT_SRCS:.c=.o}
SERVER_OBJS	= ${SERVER_SRCS:.c=.o}

RM		= rm -rf

LINK_FLAGS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf
all:	$(LIBFT) $(PRINTF) $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(SERVER): $(SERVER_OBJS) $(LIBFT) $(PRINTF)
		$(CC) $(CFLAGS) $(SERVER_OBJS) $(LINK_FLAGS) -o $(SERVER)
		@echo "SERVER IS READY, COMMANDER!"

$(CLIENT): $(CLIENT_OBJS) $(LIBFT) $(PRINTF)
		$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LINK_FLAGS) -o $(CLIENT)
		@echo "CLIENT IS ALSO READY, COMMANDER!"
clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	@echo "OPERATIONS SUCCESSFUL. UNTIL NEXT TIME, COMMANDER!"

re: fclean all

.PHONY: all clean fclean re libft ft_printf
