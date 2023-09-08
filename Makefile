# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 18:33:35 by jsarabia          #+#    #+#              #
#    Updated: 2023/09/08 16:44:55 by jsarabia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =				\
		death.c \
		actions.c \
		messages.c \
		evolution.c \
		philo_utils.c \
		philosophers.c \

OBJS = $(SRC:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=thread #-fsanitize=address #-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(OBJS) $(NAME)

re: fclean all

.PHONY:		all clean fclean re
