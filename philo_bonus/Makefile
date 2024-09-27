# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 15:09:09 by lamhal            #+#    #+#              #
#    Updated: 2024/09/26 15:10:05 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  philo_bonus
CC = cc #-g -fsanitize=thread
CFLAGS = -Wall -Werror -Wextra

SRC = parsing.c main.c fill_var.c process.c utils.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c philo.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: clean