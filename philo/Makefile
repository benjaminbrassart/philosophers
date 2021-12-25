# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 01:39:23 by bbrassar          #+#    #+#              #
#    Updated: 2021/12/23 10:12:00 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= philo
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -c -MMD -MP -I.
LDLIBS				= -lpthread

ifdef DEBUG
CFLAGS				+= -g$(DEBUG)
endif

DIR_SRC				= src
DIR_OBJ				= obj
SRC					= main.c utils.c init.c run.c routine.c autolock.c
OBJ					= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP					= $(OBJ:.o=.d)

$(NAME):			$(OBJ)
					$(CC) $^ -o $@ $(LDLIBS)

-include $(DEP)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) $< -o $@

all:				$(NAME)

clean:
					rm -rf $(DIR_OBJ)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
