# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 08:37:12 by kecheong          #+#    #+#              #
#    Updated: 2024/11/14 18:06:12 by kecheong         ###   ########.fr        #
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
	LDFLAGS := -Lmlx_mac -Llibft
	LDLIBS := -lmlx -lft
	includes := -Imlx_mac -Iinclude -Ilibft/includes
	framework := -framework OpenGL -framework AppKit
else
	MLX_dir := mlx_linux
	MLX := $(MLX_dir)/libmlx_Linux.a
	LDFLAGS := -Lmlx_linux -Llibft
	LDLIBS := -lmlx_Linux -lft -lXext -lX11 -lm -lz
	includes := -Imlx_linux -Iinclude -Ilibft/includes
endif

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

src_dir := src
dirs := $(src_dir) \
		$(src_dir)/map \
		$(src_dir)/player \
		$(src_dir)/mlx_utils \
		$(src_dir)/raycast \
		$(src_dir)/renderer \
		$(src_dir)/minimap \
		$(src_dir)/keys

srcs := $(foreach dir, $(dirs), $(wildcard $(dir)/*.c))

obj_dir := obj
objs := $(srcs:$(src_dir)/%.c=$(obj_dir)/%.o)

.PHONY: all
all: $(MLX) $(NAME)

$(MLX):
	make -C $(MLX_dir)

$(NAME): $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework)  -o $(NAME)

$(obj_dir):
	mkdir -p $(obj_dir)

$(obj_dir)/%.o: $(src_dir)/%.c | obj
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

.PHONY: clean
clean:
	$(RM) -r $(obj_dir)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: optimized
optimized: CFLAGS += -O3
optimized: all

.PHONY: debug
debug: CFLAGS += -g3
debug: all

.PHONY: fsan
fsan: CFLAGS += -fsanitize=address,undefined -g3
fsan: all

.PHONY: norminette
norminette:
	norminette $(src_dir) include/
