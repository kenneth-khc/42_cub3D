/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 01:30:51 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 23:55:56 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colours.h"
#include "Game.h"
#include "libft.h"

static bool	is_texture(const char *type_identifier);
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
		if (is_texture(configurable->type_identifier))
		{
			set_texture(game, &renderer, configurable);
		}
		else if (is_colour(configurable->type_identifier))
		{
			set_colour(&renderer, configurable);
		}
		i++;
	}
	return (renderer);
}

static
void	set_texture(t_game *game, t_renderer *renderer,
					t_configurable *configurable)
{
	t_image		*renderer_img_slot;
	const char	*texture_filepath = configurable->line
		+ configurable->value_offset;

	renderer_img_slot = NULL;
	if (ft_strcmp(configurable->type_identifier, "NO") == 0)
	{
		renderer_img_slot = &renderer->wall_textures[NORTH];
	}
	else if (ft_strcmp(configurable->type_identifier, "SO") == 0)
	{
		renderer_img_slot = &renderer->wall_textures[SOUTH];
	}
	else if (ft_strcmp(configurable->type_identifier, "EA") == 0)
	{
		renderer_img_slot = &renderer->wall_textures[EAST];
	}
	else if (ft_strcmp(configurable->type_identifier, "WE") == 0)
	{
		renderer_img_slot = &renderer->wall_textures[WEST];
	}
	load_image(game, renderer_img_slot, texture_filepath);
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

static
bool	is_texture(const char *type_identifier)
{
	if (ft_strcmp(type_identifier, "NO") == 0
		|| ft_strcmp(type_identifier, "SO") == 0
		|| ft_strcmp(type_identifier, "WE") == 0
		|| ft_strcmp(type_identifier, "EA") == 0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

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
