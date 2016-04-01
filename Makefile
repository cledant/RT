# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 09:31:19 by vlize             #+#    #+#              #
#    Updated: 2016/03/31 16:31:29 by tpierron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRC =	main.c init.c error.c create_img_text_list.c parser_1.c parsing_func_1.c \
		raytracer.c sub_function_2.c get_color.c find_intersect.c object_1.c \
		object_2.c rotation.c sub_function_1.c normal.c calc_color.c menu.c \
		reflection.c post_treatment.c modify_object.c proc_texture.c free.c\
		anti_aliasing.c perlin.c object_3.c ray_collision.c csg_create.c csg.c \
		csg_list.c csg_union.c csg_difference.c csg_intersection.c free2.c \
		is_in_shadow.c perlin3d.c norm_disturb.c mouse.c keyboard.c \
		mouse_keyboard.c menu_2.c perlin3d_2.c normal2.c image.c color_management.c\
		create_mat_light_list.c create_obj_list.c parser_2.c parsing_func_2.c \
		parsing_func_3.c parsing_func_4.c save_img.c sub_function_3.c \
		sub_function_4.c check_parsing.c xml_check_image.c xml_check_tex_id.c \
		free3.c free4.c xml_check_obj_id.c

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
