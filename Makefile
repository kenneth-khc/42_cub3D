# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 08:37:12 by kecheong          #+#    #+#              #
#    Updated: 2025/04/24 03:30:44 by kecheong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
BONUS_NAME := $(NAME)_bonus

uname := $(shell uname)

CC := cc
CFLAGS := -Wall -Werror -Wextra -MMD -g3 #-fsanitize=address

LDFLAGS := $(addprefix -L, libft)
LDLIBS := $(addprefix -l, mlx ft)
includes := $(addprefix -I, include/common libft/includes)

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

minilibx := $(minilibx_dir)/libmlx.a

libft_dir := libft
libft := $(libft_dir)/libft.a

src_dir := src
common := $(src_dir)/common
mandatory := $(src_dir)/mandatory
bonus := $(src_dir)/bonus

common_srcs := src/common/main.c
common_srcs += $(addprefix $(common)/parser/, parse.c config.c file_helpers.c)
common_srcs += $(addprefix $(common)/map/, map.c map_padding.c map_validation.c map_utils.c)
common_srcs += $(addprefix $(common)/keys/, init.c key_events.c movement_keys.c camera_keys.c)
common_srcs += $(addprefix $(common)/player/, init.c)
common_srcs += $(addprefix $(common)/raycast/, init.c raycast.c raycast_utils.c)
common_srcs += $(addprefix $(common)/renderer/, bresenham.c)
common_srcs += $(addprefix $(common)/utils/, utils.c math_utils.c collision.c)
common_srcs += $(addprefix $(common)/mouse/, mouse.c)
common_srcs += $(addprefix $(common)/mlx_utils/, draw.c image.c colors.c pixels.c)
$(info $$(common_srcs) == $(common_srcs))

# TODO: subdirectories
mandatory_srcs := $(addprefix $(mandatory)/, game_init.c game_update.c keybinds.c render.c \
		  render_utils.c renderer_init.c ui_keys.c)

bonus_srcs := $(addprefix $(bonus)/, game_init.c game_update.c keybinds.c render.c \
		  render_utils.c renderer_init.c ui_keys.c animation.c animation_utils.c)
bonus_srcs += $(addprefix $(bonus)/minimap/, init.c minimap.c)

obj_dir := obj

ifeq ($(filter bonus, $(MAKECMDGOALS)), bonus)
includes += -Iinclude/bonus
objs := $(patsubst src/common/%.c, obj/bonus/common/%.o, $(common_srcs)) \
		$(patsubst src/bonus/%.c, obj/bonus/bonus/%.o, $(bonus_srcs))
else
includes += -Iinclude/mandatory
objs := $(patsubst src/common/%.c, obj/mandatory/common/%.o, $(common_srcs)) \
		$(patsubst src/mandatory/%.c, obj/mandatory/mandatory/%.o, $(mandatory_srcs))
endif

dependencies := $(objs:%.o=%.d)

green := \e[0;32m
reset := \e[0;0m

# all: mandatory bonus

.PHONY: all
all: $(minilibx) $(libft) $(NAME)

# mandatory: $(NAME)
#
bonus: $(BONUS_NAME)

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n$(reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

$(minilibx):
	make -C $(minilibx_dir)

$(NAME): $(libft) $(minilibx) $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework) -o $(NAME)

$(BONUS_NAME): $(libft) $(minilibx) $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework) -o $(BONUS_NAME)

$(obj_dir):
	mkdir -p $(obj_dir)

$(obj_dir)/mandatory/common/%.o: $(src_dir)/common/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

$(obj_dir)/mandatory/mandatory/%.o: $(src_dir)/mandatory/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

$(obj_dir)/bonus/common/%.o: $(src_dir)/common/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

$(obj_dir)/bonus/bonus/%.o: $(src_dir)/bonus/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@


$(obj_dir)/%.o: $(src_dir)/%.c | obj
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

.PHONY: clean
clean:
	$(RM) -r $(obj_dir)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

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
