/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:38:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/12 01:58:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"
#include "Raycaster.h"
#include "Utils.h"
#include "Vector.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

extern char	g_layout[10][10];

void	raycast(t_raycaster *raycaster, t_player *player, t_game *game)
{
	t_ray	*ray;

	update_raycaster(raycaster, &game->player);
	for (int x = 0; x < game->screen_width; x++)
	{
		ray = &raycaster->rays[x];
		cast(ray, player, &game->map, game);
		/*get_shortest_distance(ray, player, raycaster);*/
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

	raycaster->number_of_rays = game->screen_width;
	raycaster->angle_increment = player->field_of_view / raycaster->number_of_rays;
	// TODO: are these angles correct?
	raycaster->leftmost_ray_angle = player->angle_in_radians + (player->field_of_view / 2);
	/*raycaster->rightmost_ray_angle = player->angle_in_radians - (player->field_of_view / 2);*/

	/*raycaster->projection_plane.x = 0;*/
	/*raycaster->projection_plane.y = 1; // the projection plane stretches out 1 y left and 1 y right of the player*/
	i = 0;
	// TODO: is this even necessary
	while (i < raycaster->number_of_rays)
	{
		// coordinate within the "projection plane", 0 being the left to 1 being the right
		/*double	camera_x = 2 * i / (double)raycaster->number_of_rays - 1;*/
		ray = &raycaster->rays[i];
		memset(ray, 0, sizeof(t_ray));
		ray->id = i;
		ray->world_pos = player->world_pos;
		ray->map_pos.x = player->world_pos.x / TILE_WIDTH;
		ray->map_pos.y = player->world_pos.y / TILE_HEIGHT;
		ray->frac_map_pos.x = player->world_pos.x / TILE_WIDTH;
		ray->frac_map_pos.y = player->world_pos.y / TILE_HEIGHT;
		ray->angle_in_radians
			= raycaster->leftmost_ray_angle - (ray->id * raycaster->angle_increment);
		/*ray->dir.x = player->direction.x + raycaster->projection_plane.x * camera_x;*/
		/*ray->dir.y = player->direction.y + raycaster->projection_plane.y * camera_x;*/
		/*double	dir_x = cos(player->angle_in_radians); (void)dir_x;*/
		/*double	dir_y = -sin(player->angle_in_radians); (void)dir_y;*/
		ray->dir.x = cos(ray->angle_in_radians);
		ray->dir.y = -sin(ray->angle_in_radians);
		ray->x_unit = game->tile_width;
		ray->y_unit = game->tile_height;
		i++;
	}
}

/* Update the raycaster's angles and positions based on the new player
 * angles and positions */
void	update_raycaster(t_raycaster *raycaster, t_player *player)
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
		ray->map_pos.x = player->world_pos.x / TILE_WIDTH;
		ray->map_pos.y = player->world_pos.y / TILE_HEIGHT;
		ray->frac_map_pos.x = player->world_pos.x / TILE_WIDTH;
		ray->frac_map_pos.y = player->world_pos.y / TILE_HEIGHT;
		ray->angle_in_radians =
			raycaster->leftmost_ray_angle - (ray->id * raycaster->angle_increment);
		ray->dir.x = cos(ray->angle_in_radians);
		ray->dir.y = -sin(ray->angle_in_radians);
		i++;
	}
}

/* Send forth a ray until it hits a wall. Behold, my wizard casting powers */
void	cast(t_ray *ray, t_player *player, t_map *map, t_game *game)
{(void)ray, (void)player, (void)game, (void)map;

	// INFO: The following are equivalent. Why? I dunno bruh
	/*ray->dx = sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));*/
	/*ray->dy = sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));*/
	ray->dx = fabs(1 / ray->dir.x);
	ray->dy = fabs(1 / ray->dir.y);

	double	sideDistX, sideDistY;
	if (ray->dir.x < 0)
	{
		ray->x_step = -1;
		sideDistX = (ray->frac_map_pos.x - ray->map_pos.x) * ray->dx;
	}
	else
	{
		ray->x_step = +1;
		sideDistX = (ray->map_pos.x + 1 - ray->frac_map_pos.x) * ray->dx;
	}
	if (ray->dir.y < 0)
	{
		ray->y_step = -1;
		sideDistY = (ray->frac_map_pos.y - ray->map_pos.y) * ray->dy;
	}
	else
	{
		ray->y_step = +1;
		sideDistY = (ray->map_pos.y + 1 - ray->frac_map_pos.y) * ray->dy;
	}

	ray->hit = false;
	while (!ray->hit)
	{
		ray->hit_vertical = false;
		ray->hit_horizontal = false;
		if (sideDistX < sideDistY)
		{
			sideDistX += ray->dx;
			ray->map_pos.x += ray->x_step;
			ray->hit_vertical = true;
		}
		else
		{
			sideDistY += ray->dy;
			ray->map_pos.y += ray->y_step;
			ray->hit_horizontal = true;
		}
		if (is_wall(map, ray->map_pos.x, ray->map_pos.y))
		{
			ray->hit = true;
		}
	}
	if (ray->hit_vertical)
	{
		ray->distance_travelled = sideDistX - ray->dx;
	}
	else
	{
		ray->distance_travelled = sideDistY - ray->dy;
	}
}
