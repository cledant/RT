# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 09:31:19 by vlize             #+#    #+#              #
#    Updated: 2016/03/04 13:44:53 by tpierron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRC =	rt.c rt_exit.c rt_init.c rt_read.c rt_make.c rt_set.c \
			rt_draw.c rt_equation.c rt_sub_function.c rt_object.c \
			rt_normal.c rt_spot.c rt_lux.c rt_object2.c rt_normal2.c \
			rt_check.c

LIB =	-L ./libft/ -lft \
		-lmlx -lm \
		-framework OpenGL -framework AppKit

INC =	-I ./include/ \
		-I /usr/local/include/ \
		-I /System/Library/Frameworks/Tk.framework/Headers/

OBJ = $(SRC:%.c=obj/%.o)

SRC_PATH = ./src/

OBJ_PATH = ./obj/

CMP = gcc -Wall -Wextra -Werror

.PHONY: all clean fclean re

all : obj $(NAME)

obj:
		@ mkdir obj

$(NAME) : $(OBJ)
		@ make -C libft/
		@ $(CMP) -o $(NAME) $(OBJ) $(LIB)
		@ echo "\x1b[32m>make all : \tOK\x1b[0m"

obj/%.o: $(SRC_PATH)/%.c
		@ $(CMP) $(INC) -o $@ -c $<

clean :
		@ make -C libft/ clean
		@ rm -rf obj
		@ echo "\x1b[32m>make clean :\tOK\x1b[0m"

fclean : clean
		@ make -s -C libft/ fclean
		@ rm -rf $(NAME)
		@ echo "\x1b[32m>make fclean :\tOK\x1b[0m"

re : fclean all
		@ echo "\x1b[32m>make re :  \tOK\x1b[0m"
