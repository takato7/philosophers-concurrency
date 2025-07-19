# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:46:43 by tmitsuya          #+#    #+#              #
#    Updated: 2025/04/24 12:34:45 by tmitsuya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo_bonus
SRC				= ft_clean_exit.c \
				  ft_cleanup.c \
				  ft_create_monitor_thread.c \
				  ft_crtsct_utils.c \
				  ft_eating.c \
				  ft_init_philos.c \
				  ft_init_semaphore.c \
				  ft_start_routine.c \
				  ft_start_simulate.c \
				  ft_syscalls_i.c \
				  ft_syscalls_ii.c \
				  ft_time_check_and_logging.c \
				  ft_time_utils.c \
				  ft_utils_itoa.c \
				  ft_utils.c \
				  main.c 
OBJ_DIR 		= obj
OBJ 			= $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
HDR				= philo_bonus.h
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -pthread
RM 				= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)/

fclean: clean
	$(RM) $(NAME)

re: fclean all

memory: CFLAGS += -g3 -fsanitize=address
memory: re

thread: CFLAGS += -g3 -fsanitize=thread
thread: re

rm:
	$(RM) /dev/shm/*

bonus: $(NAME)

.PHONY: all clean fclean re memory thread rm bonus