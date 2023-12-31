# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferjul <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 19:12:28 by dferjul           #+#    #+#              #
#    Updated: 2023/12/04 07:27:37 by dferjul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(shell find ./ -name '*.c')

OBJ_DIR = obj_o

# Extraire les noms de dossiers à partir de la variable SRCS #
DIR := $(sort $(dir $(SRC)))

OBJS	=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CC	=	gcc

CFLAGS	=	-g -Wall -Wextra -Werror -I./include

#CFLAGS	=	-pthread -g

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
