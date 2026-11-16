# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 15:12:03 by gdero             #+#    #+#              #
#    Updated: 2024/12/28 12:36:41 by ngharian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  srcs/main.c \
		srcs/utils.c \
		srcs/start.c \
		srcs/threading.c \
		srcs/routine.c

OBJECTS = $(SRCS:.c=.o)

HEADER = philo.h

NAME = philo

CFLAGS = -g -Wall -Wextra -Werror

CC = gcc

RM = rm -f

$(NAME): $(OBJECTS)
	@printf "\033[K\033[0;34mFiles compiled.\n"
	@$(CC) $(CFLAGS) ${OBJECTS} ${LIBFT} -I ${HEADER} -o ${NAME}
	@printf "\r\033[0;31mBinary ready.\033[0m\n"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@sleep 0.001
	@printf "\033[K\033[0;32mCompiling the files... : \033[0;33m%s\r" "$<"
	
all: $(NAME)
	
clean:
	@$(RM) $(OBJECTS)
	@sleep 0.5
	@printf "\033[0;32mEverything is clean.\033[0m\n"

fclean: clean
	@$(RM) $(NAME)
	@sleep 1
	@printf "\033[0;31mBinary destroyed.\033[0m\n"

re: fclean all

.PHONY: all clean fclean re msg
