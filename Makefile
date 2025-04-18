# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 08:37:12 by kecheong          #+#    #+#              #
#    Updated: 2025/04/19 01:29:22 by kecheong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := debug

GREEN := \e[0;32m
C_RESET := \e[0;0m

NAME := cub3D
UNAME := $(shell uname)

CC := cc
CFLAGS := -Wall -Werror -Wextra -MMD

ifeq ($(UNAME), Darwin)
	MLX_dir := mlx_mac
	MLX := $(MLX_dir)/libmlx.a
	LDFLAGS := $(addprefix -L, mlx_mac libft)
	LDLIBS := $(addprefix -l, mlx ft)
	includes := $(addprefix -I, mlx_mac include libft/includes)
	framework := $(addprefix -framework, OpenGL AppKit)
else
	MLX_dir := mlx_linux
	MLX := $(MLX_dir)/libmlx_Linux.a
	LDFLAGS := $(addprefix -L, mlx_linux libft)
	LDLIBS := $(addprefix -l, mlx_Linux ft Xext X11 m z)
	includes := $(addprefix -I, mlx_linux include libft/includes)
endif

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

src_dir := src
dirs := $(src_dir) \
		$(src_dir)/parser \
		$(src_dir)/map \
		$(src_dir)/player \
		$(src_dir)/mlx_utils \
		$(src_dir)/raycast \
		$(src_dir)/renderer \
		$(src_dir)/minimap \
		$(src_dir)/keys \
		$(src_dir)/textures

srcs := $(foreach dir, $(dirs), $(wildcard $(dir)/*.c))

obj_dir := obj
objs := $(srcs:$(src_dir)/%.c=$(obj_dir)/%.o)
dependencies := $(objs:%.o=%.d)

.PHONY: all
all: $(MLX) $(LIBFT) $(NAME)

$(LIBFT):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(GREEN)Initializing libft submodule...\n$(C_RESET)" ; \
		git submodule update --init ; \
	fi
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_dir)

$(NAME): $(LIBFT) $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework) -o $(NAME)

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

.PHONY: libclean
libclean:
	make clean -C $(LIBFT_DIR)

.PHONY: libfclean
libfclean:
	make fclean -C $(LIBFT_DIR)

.PHONY: re
re: fclean all

.PHONY: release
release: CFLAGS += -O3
release: all

.PHONY: debug
debug: CFLAGS += -g3
debug: all

.PHONY: fsan
fsan: CFLAGS += -fsanitize=address,undefined -g3
fsan: all

.PHONY: norminette
norminette:
	norminette $(src_dir) include/

-include $(dependencies)
