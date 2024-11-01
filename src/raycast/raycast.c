/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:38:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 17:46:26 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"
#include "Raycaster.h"
#include "Utils.h"
#include "Vector.h"

void	init_raycaster(t_raycaster *raycaster, t_player *player, t_game *game)
{
	int		i;
	t_ray	*ray;

	raycaster->number_of_rays = game->screen_width;
	i = 0;
	while (i < raycaster->number_of_rays)
	{ // TODO: probably not necessary to initialize a ray's fields to 0
		memset(&raycaster->rays[i], 0, sizeof(t_ray));
		i++;
	}
	raycaster->angle_increment = player->field_of_view / raycaster->number_of_rays;
	// TODO: are these angles correct?
	raycaster->leftmost_ray_angle = player->angle_in_radians + (player->field_of_view / 2);
	raycaster->rightmost_ray_angle = player->angle_in_radians - (player->field_of_view / 2);
	// TODO: should we set up all the rays before firing them or set up as we fire them?
	i = 0;
	while (i < raycaster->number_of_rays)
	{
		ray = &raycaster->rays[i];
		ray->map_pos = copy_vector_int(&player->map_pos);
		ray->world_pos = copy_vector_double(&player->world_pos);
		ray->angle_in_radians = raycaster->leftmost_ray_angle + (raycaster->angle_increment * i);
		ray->direction.x = cos(ray->angle_in_radians);
		ray->direction.y = -sin(ray->angle_in_radians); // TODO: do I need to inverse this sin as our y axis is flipped?
		find_first_x_intersect(ray, game);
		ray->horizontal_wall_pos = dda(raycaster, ray, game, &game->map);
		find_first_y_intersect(ray, game);
		ray->vertical_wall_pos = dda(raycaster, ray, game, &game->map);
		i++;
	}
}

void	find_first_x_intersect(t_ray *ray, t_game *game)
{
	if (ray->direction.y < 0) // ray is flying upwards
	{
		ray->first_x_intersect.y = floor(ray->world_pos.y / game->tile_height)
									* game->tile_height - 1;
		ray->y_step = -game->tile_height;
	}
	else if (ray->direction.y > 0) // ray is flying downwards
	{
		ray->first_x_intersect.y = floor(ray->world_pos.y / game->tile_height)
									* game->tile_height + game->tile_height;
		ray->y_step = game->tile_height;
	}
	// triangles!
	double	opposite_length;
	double	adjacent_length;

	opposite_length = ray->world_pos.y - ray->first_x_intersect.y;
	adjacent_length = opposite_length / tan(ray->angle_in_radians);
	ray->first_x_intersect.x = ray->world_pos.x + adjacent_length;
	ray->x_step = game->tile_height / tan(ray->angle_in_radians);
}

void	find_first_y_intersect(t_ray *ray, t_game *game)
{
	if (ray->direction.x < 0) // ray is flying left
	{
		ray->first_y_intersect.x = floor(ray->world_pos.x / game->tile_width)
									* game->tile_width - 1;
		ray->x_step = -game->tile_width;
	}
	else if (ray->direction.x > 0)
	{
		ray->first_y_intersect.x = floor(ray->world_pos.x / game->tile_width)
									* game->tile_width + game->tile_width;
		ray->x_step = game->tile_width;
	}
	// triangles!!!!!
	double	opposite_length;
	double	adjacent_length;

	adjacent_length = ray->world_pos.x - ray->first_y_intersect.x;
	opposite_length = tan(ray->angle_in_radians) * adjacent_length;
	ray->first_y_intersect.y = ray->world_pos.y + opposite_length;
	ray->y_step = game->tile_width * tan(ray->angle_in_radians);
}

#include <stdio.h>
t_vector_double	dda(t_raycaster *raycaster, t_ray *ray, t_game *game, t_map *map)
{ (void)game; (void)raycaster;
	t_vector_double	ray_pos;
	
	ray->hit_wall = false;
	ray_pos = copy_vector_double(&ray->first_x_intersect);
	while (!ray->hit_wall)
	{
		ray->map_pos = world_to_map_pos(&ray_pos);
		if (map->layout[ray->map_pos.y][ray->map_pos.x] == '1')
		{
			ray->hit_wall = true;
			ray->horizontal_wall_pos = copy_vector_double(&ray_pos);
			return (copy_vector_double(&ray_pos));
		}
		ray_pos.x += ray->x_step;
		ray_pos.y += ray->y_step;
	}
	// TODO: ???
	return ray_pos;
}

void	raycast(t_raycaster *raycaster, t_game *game, t_player *player)
{
	int		i;
	t_ray	*ray;

	init_raycaster(raycaster, player, game);
	i = 0;
	while (i < raycaster->number_of_rays)
	{
		ray = &raycaster->rays[i];
		i++;
	}
}
