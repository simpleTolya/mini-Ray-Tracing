# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marmand <marmand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 14:48:43 by marmand           #+#    #+#              #
#    Updated: 2022/02/21 21:37:23 by marmand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = ft_hooks.c \
		ft_init_objects.c \
		ft_init_objects2.c \
		ft_objects_get_normal.c \
		ft_objects_intersect.c \
		ft_render.c \
		ft_utils.c \
		ft_utils2.c \
		main.c \
		ft_compute_light.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

NAME = miniRT

all: $(NAME)

%.o: %.c miniRT.h ft_objects.h
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(GNL) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C libft

clean:
	$(MAKE) fclean -C libft
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus: all

.PHONY = all clean fclean re bonus
