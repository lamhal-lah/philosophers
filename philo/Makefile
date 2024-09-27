# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 17:09:56 by lamhal            #+#    #+#              #
#    Updated: 2024/09/25 15:24:23 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  philo
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