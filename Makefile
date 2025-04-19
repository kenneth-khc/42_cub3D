# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 08:37:12 by kecheong          #+#    #+#              #
#    Updated: 2025/04/20 00:14:26 by kecheong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
BONUS_NAME := $(NAME)_bonus

uname := $(shell uname)

CC := cc
CFLAGS := -Wall -Werror -Wextra -MMD

LDFLAGS := $(addprefix -L, libft)
LDLIBS := $(addprefix -l, mlx ft)
includes := $(addprefix -I, include/mandatory libft/includes)

ifeq ($(uname), Darwin)
	minilibx_dir := mlx_mac
	includes += $(addprefix -I, mlx_mac)
	framework := $(addprefix -framework, OpenGL AppKit)
	LDFLAGS += $(addprefix -L, mlx_mac)
else
	minilibx_dir := mlx_linux
	includes += $(addprefix -I, mlx_linux)
	LDFLAGS += $(addprefix -L, mlx_linux)
	LDLIBS += $(addprefix -l, Xext X11 m z)
endif

minilibx := $(minilibx_dir)/libmlx.a

libft_dir := libft
libft := $(libft_dir)/libft.a

src_dir := src/mandatory
dirs := $(src_dir) \
		$(src_dir)/parser \
		$(src_dir)/map \
		$(src_dir)/player \
		$(src_dir)/mlx_utils \
		$(src_dir)/raycast \
		$(src_dir)/renderer \
		$(src_dir)/keys
#		$(src_dir)/textures
#		$(src_dir)/minimap \

srcs := $(foreach dir, $(dirs), $(wildcard $(dir)/*.c))

obj_dir := obj
objs := $(srcs:$(src_dir)/%.c=$(obj_dir)/%.o)
dependencies := $(objs:%.o=%.d)

green := \e[0;32m
reset := \e[0;0m

.PHONY: all
all: $(minilibx) $(libft) $(NAME)

ifeq ($(filter bonus, $(MAKECMDGOALS)), bonus)

endif

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n$(reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

$(minilibx):
	make -C $(minilibx_dir)

$(NAME): $(libft) $(objs)
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
	make clean -C $(libft_dir)

.PHONY: libfclean
libfclean:
	make fclean -C $(libft_dir)

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
