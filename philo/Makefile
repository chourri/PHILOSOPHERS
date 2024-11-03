# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chourri <chourri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 10:31:05 by chourri           #+#    #+#              #
#    Updated: 2024/09/28 17:33:39 by chourri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f
SRCS = philo.c \
 initialization.c \
 libft_tools.c \
 monitor.c \
 parsing.c \
 routine.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.c philo.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
