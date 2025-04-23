# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 08:37:12 by kecheong          #+#    #+#              #
#    Updated: 2025/04/24 04:56:39 by kecheong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
BONUS_NAME := $(NAME)_bonus

build_type ?= debug
# compiler options
CC := cc
ifeq ($(build_type), debug)
CFLAGS := -Wall -Werror -Wextra -MMD -g3
else ifeq ($(build_type), fsan)
CFLAGS := -Wall -Werror -Wextra -MMD -g3 -fsanitize=address
else ifeq ($(build_type), release)
CFLAGS := -Wall -Werror -Wextra -O3
endif
LDFLAGS := $(addprefix -L, libft)
LDLIBS := $(addprefix -l, mlx ft)
includes := $(addprefix -I, include/common include/$(VERSION) libft/includes)

# Linux or MacOS
uname := $(shell uname)
ifeq ($(uname), Darwin)
	minilibx_dir := mlx_mac
	includes += $(addprefix -I, mlx_mac)
	framework := $(addprefix -framework, OpenGL AppKit)
	LDFLAGS += $(addprefix -L, mlx_mac)
else
	minilibx_dir := mlx_linux
	includes += $(addprefix -I, mlx_linux)
	LDFLAGS += $(addprefix -L, mlx_linux)
	LDLIBS += $(addprefix -l, Xext X11 m z Xfixes)
endif

# libraries
minilibx := $(minilibx_dir)/libmlx.a
libft_dir := libft
libft := $(libft_dir)/libft.a

# source directories
src_dir := src
common := $(src_dir)/common
version := $(src_dir)/$(VERSION)
mandatory := $(src_dir)/mandatory
bonus := $(src_dir)/bonus

# common sources
common_srcs := src/common/main.c \
	$(addprefix $(common)/parser/, parse.c config.c file_helpers.c) \
	$(addprefix $(common)/map/, map.c map_padding.c map_validation.c map_utils.c) \
	$(addprefix $(common)/keys/, init.c key_events.c movement_keys.c camera_keys.c) \
	$(addprefix $(common)/player/, init.c) \
	$(addprefix $(common)/raycast/, init.c raycast.c raycast_utils.c) \
	$(addprefix $(common)/renderer/, bresenham.c) \
	$(addprefix $(common)/utils/, utils.c math_utils.c collision.c) \
	$(addprefix $(common)/mouse/, mouse.c) \
	$(addprefix $(common)/mlx_utils/, draw.c image.c colors.c pixels.c)

# mandatory sources
mandatory_srcs := $(addprefix $(mandatory)/, game_init.c game_update.c) \
	$(addprefix $(mandatory)/keys/, keybinds.c ui_keys.c) \
	$(addprefix $(mandatory)/renderer/, init.c render.c render_utils.c)

# bonus sources
bonus_srcs := $(addprefix $(bonus)/, game_init.c game_update.c) \
	$(addprefix $(bonus)/keys/, keybinds.c ui_keys.c) \
	$(addprefix $(bonus)/renderer/, init.c render.c render_utils.c) \
	$(addprefix $(bonus)/minimap/, init.c minimap.c) \
	$(addprefix $(bonus)/animation/, animation.c animation_utils.c)

# object files depending on mandatory or bonus
obj := obj/$(build_type)
ifeq ($(VERSION), mandatory)
objs := $(patsubst src/common/%.c, $(obj)/mandatory/common/%.o, $(common_srcs)) \
		$(patsubst src/mandatory/%.c, $(obj)/mandatory/mandatory/%.o, $(mandatory_srcs))
else ifeq ($(VERSION), bonus)
objs := $(patsubst src/common/%.c, $(obj)/bonus/common/%.o, $(common_srcs)) \
		$(patsubst src/bonus/%.c, $(obj)/bonus/bonus/%.o, $(bonus_srcs))
endif

dependencies := $(objs:%.o=%.d)

# colours
green := \033[0;32m
reset := \033[0;0m

all: mandatory bonus
	@printf "$(green)Done compiling $(NAME) and $(BONUS_NAME)!$(reset)\n"

mandatory:
	@echo Compiling mandatory...
	@$(MAKE) VERSION=mandatory --no-print-directory cub3D

bonus:
	@echo Compiling bonus...
	@$(MAKE) VERSION=bonus --no-print-directory cub3D_bonus

$(NAME): $(libft) $(minilibx) $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework) -o $(NAME)
	@printf "$(green)Mandatory compiled!$(reset)\n"

$(BONUS_NAME): $(libft) $(minilibx) $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework) -o $(BONUS_NAME)
	@printf "$(green)Bonus compiled!$(reset)\n"

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n$(reset)" ; \
		git submodule update --init ; \
	fi
	@$(MAKE) -C $(libft_dir)

$(minilibx):
	@$(MAKE) -C $(minilibx_dir)

# pattern rules for object files depending on which VERSION the Makefile
# is invoked with
$(obj)/$(VERSION)/common/%.o: $(src_dir)/common/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

$(obj)/$(VERSION)/$(VERSION)/%.o: $(src_dir)/$(VERSION)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

.PHONY: clean
clean:
	$(RM) -r obj/

.PHONY: fclean
fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

.PHONY: libclean
libclean:
	@$(MAKE) clean -C $(libft_dir)

.PHONY: libfclean
libfclean:
	@$(MAKE) fclean -C $(libft_dir)

.PHONY: re
re: fclean all

.PHONY: release
release:
	@$(MAKE) all build_type=release --no-print-directory

.PHONY: debug
debug:
	@$(MAKE) all build_type=debug --no-print-directory

.PHONY: fsan
fsan:
	@$(MAKE) all build_type=fsan --no-print-directory

.PHONY: norminette
norminette:
	norminette $(src_dir) include/

-include $(dependencies)
