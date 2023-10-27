# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferjul <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 19:12:28 by dferjul           #+#    #+#              #
#    Updated: 2023/10/27 02:30:23 by dferjul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	philo.c \
			error.c \
			init.c \
			utils.c \
			start_philo.c \


OBJ_DIR = obj_o

# Extraire les noms de dossiers à partir de la variable SRCS #
DIR := $(sort $(dir $(SRC)))

OBJS	=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror -pthread

RM	=	rm -rf

NAME	=	philo

#--Règle pour compiler les fichiers .c en fichiers .o--#
 $(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ 

#---------------------rules---------------------#

all : $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONE : all clean fclean re
