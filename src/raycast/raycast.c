/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:38:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/02 12:28:33 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"
#include "Raycaster.h"
#include "Vector.h"
#include <assert.h>

extern char	g_layout[10][10];

static void	init_dda(t_ray *ray);
static void	get_distance(t_ray *ray, t_player *player);

void	raycast(t_raycaster *raycaster, t_player *player, t_game *game)
{
	t_ray	*ray;

	update_raycaster(raycaster, &game->player, game);
	for (int x = 0; x < game->screen.width; x++)
	{
		ray = &raycaster->rays[x];
		cast(ray, player, &game->map);
	}
}

/* Initialize the raycaster for the first time 
 * Set the number of rays to cast based on the screen width,
 * calculate the angle difference between each ray by using the field of view,
 * find the angle of where the first ray starts and the last ray ends,
 * assign an id to each ray so it knows which X of the screen slice it is */
void	init_raycaster(t_raycaster *raycaster, t_player *player, t_game *game)
{
	t_ray	*ray;
	int		i;

	raycaster->number_of_rays = game->screen.width;
	raycaster->angle_increment = player->field_of_view / raycaster->number_of_rays;
	// TODO: are these angles correct?
	raycaster->leftmost_ray_angle = player->angle_in_radians + (player->field_of_view / 2);
	raycaster->projection_plane.x = 0;
	raycaster->projection_plane.y = 1; // the projection plane stretches out 1 y left and 1 y right of the player
	i = 0;
	// TODO: is this even necessary
	while (i < raycaster->number_of_rays)
	{
		// coordinate within the "projection plane", 0 being the left to 1 being the right
		double	camera_x = 2 * i / (double)raycaster->number_of_rays - 1;
		ray = &raycaster->rays[i];
		memset(ray, 0, sizeof(t_ray));
		ray->id = i;
		ray->world_pos = player->world_pos;
		ray->tile_index.x = player->world_pos.x / game->tile_width;
		ray->tile_index.y = player->world_pos.y / game->tile_height;
		ray->tile_offset.x = player->world_pos.x / game->tile_width;
		ray->tile_offset.y = player->world_pos.y / game->tile_height;
		ray->angle_in_radians
			= raycaster->leftmost_ray_angle - (ray->id * raycaster->angle_increment);
		ray->dir.x = player->direction.x + raycaster->projection_plane.x * camera_x;
		ray->dir.y = player->direction.y + raycaster->projection_plane.y * camera_x;
		ray->dir.x = cos(ray->angle_in_radians);
		ray->dir.y = -sin(ray->angle_in_radians);
		i++;
	}
}

/* Update the raycaster's angles and positions based on the new player
 * angles and positions */
void	update_raycaster(t_raycaster *raycaster, t_player *player, t_game *game)
{
	int		i;
	t_ray	*ray;

	raycaster->leftmost_ray_angle = player->angle_in_radians + (player->field_of_view / 2);
	raycaster->rightmost_ray_angle = player->angle_in_radians - (player->field_of_view / 2);
	i = 0;
	while (i < raycaster->number_of_rays)
	{
		ray = &raycaster->rays[i];
		ray->world_pos = player->world_pos;
		ray->tile_index.x = player->world_pos.x / game->tile_width;
		ray->tile_index.y = player->world_pos.y / game->tile_height;
		ray->tile_offset.x = player->world_pos.x / game->tile_width;
		ray->tile_offset.y = player->world_pos.y / game->tile_height;
		ray->angle_in_radians =
			raycaster->leftmost_ray_angle - (ray->id * raycaster->angle_increment);
		ray->dir.x = cos(ray->angle_in_radians);
		ray->dir.y = -sin(ray->angle_in_radians);
		i++;
	}
}

/* Send forth a ray until it hits a wall. Behold, wizardry. */
void	cast(t_ray *ray, t_player *player, t_map *map)
{
	init_dda(ray);
	while (!ray->hit)
	{
		ray->side = NO_HIT;
		if (ray->x_axis_distance < ray->y_axis_distance)
		{
			ray->tile_index.x += ray->x_step;
			ray->side = HIT_VERTICAL;
			/*if (ray->angle_in_radians >= 0*/
			/*	&& ray->angle_in_radians <= M_PI)*/
			/*{*/
			/*	ray->side = HIT_SOUTH;*/
			/*}*/
			/*else*/
			/*{*/
			/*	ray->side = HIT_NORTH;*/
			/*}*/
			/*if (ray->dir.x > 0)*/
			/*	ray->side = HIT_EAST;*/
			/*else*/
			/*	ray->side = HIT_WEST;*/
			ray->x_axis_distance += ray->dx;
		}
		else
		{
			ray->tile_index.y += ray->y_step;
			ray->side = HIT_HORIZONTAL;
			/*if (ray->angle_in_radians >= degrees_to_radians(90)*/
			/*	&& ray->angle_in_radians <= degrees_to_radians(270))*/
			/*{*/
			/*	ray->side = HIT_WEST;*/
			/*}*/
			/*else*/
			/*{*/
			/*	ray->side = HIT_EAST;*/
			/*}*/
			/*if (ray->dir.y > 0)*/
			/*	ray->side = HIT_SOUTH;*/
			/*else*/
			/*	ray->side = HIT_NORTH;*/
			ray->y_axis_distance += ray->dy;
		}
		if (is_wall(map, ray->tile_index.x, ray->tile_index.y))
		{
			ray->hit = true;
			/*if (ray->side == HIT_HORIZONTAL)*/
			/*{*/
			/*	if (ray->dir.y > 0)*/
			/*		ray->side = HIT_SOUTH;*/
			/*	else*/
			/*		ray->side = HIT_NORTH;*/
			/*}*/
			/*else if (ray->side == HIT_VERTICAL)*/
			/*{*/
			/*	if (ray->dir.x > 0)*/
			/*		ray->side = HIT_EAST;*/
			/*	else*/
			/*		ray->side = HIT_WEST;*/
			/*}*/
		}
	}
	get_distance(ray, player);
}

/* Initialize parameters for DDA (digital differential analyzer)
 * Depending on the direction of the ray, we step through x and y positive or
 * negatively
 * dx dy are the distances travelled when moving from one unit to the next
 * the distance to the first intersection is calculated by taking the difference
 * between the truncated map position and the fractional map position, giving
 * us a portion within the cell, then multiplied by the dx or dy to scale it
 * down */
static void	init_dda(t_ray *ray)
{
	ray->hit = false;
	// INFO: The following are equivalent.
	// Do a bunch of derivations to find out why they're equivalent.
	/* ray->dx = sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));*/
	/* ray->dy = sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));*/
	ray->dx = fabs(1 / ray->dir.x);
	ray->dy = fabs(1 / ray->dir.y);

	if (ray->dir.x < 0)
	{
		ray->x_step = -1;
		ray->x_axis_distance = (ray->tile_offset.x - ray->tile_index.x) * ray->dx;
	}
	else
	{
		ray->x_step = +1;
		ray->x_axis_distance = (ray->tile_index.x + 1 - ray->tile_offset.x) * ray->dx;
	}
	if (ray->dir.y < 0)
	{
		ray->y_step = -1;
		ray->y_axis_distance = (ray->tile_offset.y - ray->tile_index.y) * ray->dy;
	}
	else
	{
		ray->y_step = +1;
		ray->y_axis_distance = (ray->tile_index.y + 1 - ray->tile_offset.y) * ray->dy;
	}
}

static void	get_distance(t_ray *ray, t_player *player)
{
	if (ray->side == HIT_VERTICAL)
	{
		ray->distance_travelled = ray->x_axis_distance - ray->dx;
	}
	else
	{
		ray->distance_travelled = ray->y_axis_distance - ray->dy;
	}
	// HACK: fisheye correction. implement a proper projection plane so this
	// isn't necessary
	ray->distance_travelled
		= ray->distance_travelled
			* cos(player->angle_in_radians - ray->angle_in_radians);
}
