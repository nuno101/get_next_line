# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouro <nlouro@student.42heilbronn.de>       +#+  +:+       +#+       #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 23:47:18 by nlouro              #+#    #+#            #
#    Updated: 2021/10/08 16:39:12 by nlouro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

C_FLAGS =  -c -Wall -Wextra -Werror

C_FILES = get_next_line.c	get_next_line_utils.c

OBJ_FILES = $(C_FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar -rcs $(NAME) $(OBJ_FILES)

$(OBJ_FILES): $(C_FILES)
	gcc $(C_FLAGS) $(C_FILES)

clean:
	rm -f $(OBJ_FILES) 

fclean: clean
	rm -f $(OBJ_FILES) 
	rm -f $(NAME)

re: fclean all

t:
	gcc -Wall -Wextra -Werror test/test_get_next_line.c -o test_get_next_line.out
	chmod +x test_get_next_line.out
	./test_get_next_line.out
