/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 01:30:51 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 06:24:16 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colours.h"
#include "Game.h"
#include "Animation.h"
#include "Settings.h"
#include "libft.h"

static void
load_cat_animations(t_renderer *renderer, t_dimensions screen, t_game *game);
/*static bool	is_texture(const char *type_identifier);*/
static bool	is_colour(const char *type_identifier);
static void	set_texture(t_game *game, t_renderer *renderer,
				t_configurable *configurable);
static void	set_colour(t_renderer *renderer, t_configurable *configurable);

/* Load up the textures needed by the renderer */
t_renderer	init_renderer(t_config *config,
	t_game *game, t_image *world, t_dimensions screen)
{
	t_renderer		renderer;
	t_configurable	*configurable;
	int				i;

	renderer.img = world;
	renderer.screen = screen;
	renderer.midpoint = game->screen.height / 2;
	i = 0;
	while (i < MAX_CONFIGURABLE)
	{
		configurable = &config->configurables[i];
		if (is_colour(configurable->type_identifier))
		{
			set_colour(&renderer, configurable);
		}
		else
		{
			set_texture(game, &renderer, configurable);
		}
		i++;
	}
	load_cat_animations(&renderer, screen, game);
	return (renderer);
}

static void	load_cat_animations(t_renderer *renderer, t_dimensions screen,
			t_game *game)
{
	renderer->cat = animation(game, CAT_STANDING_ANIMATION);
	renderer->cat.pos.x = screen.width - CAT_SPRITE_X_OFFSET;
	renderer->cat.pos.y = screen.height - CAT_SPRITE_Y_OFFSET;
	renderer->cat.ticks_to_advance = 10;
\
	renderer->cat_walking = animation(game, CAT_WALKING_ANIMATION);
	renderer->cat_walking.pos.x = screen.width - CAT_SPRITE_X_OFFSET;
	renderer->cat_walking.pos.y = screen.height - CAT_SPRITE_Y_OFFSET;
	renderer->cat.ticks_to_advance = 10;
\
	renderer->cat_laying = animation(game, CAT_LAYING_ANIMATION);
	renderer->cat_laying.pos.x = screen.width - CAT_SPRITE_X_OFFSET;
	renderer->cat_laying.pos.y = screen.height - CAT_SPRITE_Y_OFFSET;
	renderer->cat.ticks_to_advance = 10;
}

static
void	set_texture(t_game *game, t_renderer *renderer,
					t_configurable *configurable)
{
	t_animation		*renderer_anim_slot;
	const char		*texture_filepath = configurable->line
		+ configurable->value_offset;

	renderer_anim_slot = NULL;
	if (ft_strcmp(configurable->type_identifier, "NO") == 0)
	{
		renderer_anim_slot = &renderer->wall_animations[NORTH];
	}
	else if (ft_strcmp(configurable->type_identifier, "SO") == 0)
	{
		renderer_anim_slot = &renderer->wall_animations[SOUTH];
	}
	else if (ft_strcmp(configurable->type_identifier, "EA") == 0)
	{
		renderer_anim_slot = &renderer->wall_animations[EAST];
	}
	else if (ft_strcmp(configurable->type_identifier, "WE") == 0)
	{
		renderer_anim_slot = &renderer->wall_animations[WEST];
	}
	*renderer_anim_slot = animation(game, texture_filepath);
}

static
void	set_colour(t_renderer *renderer,
					t_configurable *configurable)
{
	const t_colour	colour = rgb_string_to_colour(configurable->line
			+ configurable->value_offset);

	if (ft_strcmp(configurable->type_identifier, "C") == 0)
	{
		renderer->ceiling = colour;
	}
	else if (ft_strcmp(configurable->type_identifier, "F") == 0)
	{
		renderer->floor = colour;
	}
}

/*static*/
/*bool	is_texture(const char *type_identifier)*/
/*{*/
/*	if (ft_strcmp(type_identifier, "NO") == 0*/
/*		|| ft_strcmp(type_identifier, "SO") == 0*/
/*		|| ft_strcmp(type_identifier, "WE") == 0*/
/*		|| ft_strcmp(type_identifier, "EA") == 0)*/
/*	{*/
/*		return (true);*/
/*	}*/
/*	else*/
/*	{*/
/*		return (false);*/
/*	}*/
/*}*/

static
bool	is_colour(const char *type_identifier)
{
	if (ft_strcmp(type_identifier, "C") == 0
		|| ft_strcmp(type_identifier, "F") == 0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
