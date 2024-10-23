# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 08:37:12 by kecheong          #+#    #+#              #
#    Updated: 2024/10/23 10:27:16 by kytan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
UNAME := $(shell uname)
$(info $$(UNAME) = $(UNAME))

CC := cc
CFLAGS := -Wall -Werror -Wextra

ifeq ($(UNAME), Darwin)
	MLX_dir := mlx_mac
	MLX := $(MLX_dir)/libmlx.a
	LDFLAGS := -Lmlx_mac
	LDLIBS := -lmlx
	includes := -Imlx_mac
	framework := -framework OpenGL -framework AppKit
else
	MLX_dir := mlx_linux
	MLX := $(MLX_dir)/libmlx_Linux.a
	LDFLAGS := -Lmlx_linux
	LDLIBS := -lmlx_Linux -lXext -lX11 -lm -lz
	includes := -Imlx_linux
endif

srcs := test_mlx.c
obj_dir := obj
objs := $(addprefix obj/, $(srcs:.c=.o))

.PHONY: all
all: $(MLX) $(NAME)

$(MLX):
	make -C $(MLX_dir)

$(NAME): $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework)  -o $(NAME)

$(obj_dir):
	mkdir -p $(obj_dir)

$(obj_dir)/%.o: %.c | obj
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

.PHONY: clean
clean:
	$(RM) -r $(obj_dir)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: debug
debug: CFLAGS += -g3
debug: all

.PHONY: fsan
fsan: CFLAGS += -fsanitize=address -g3
fsan: all
