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
	raycaster->rightmost_ray_angle = player->angle_in_radians - (player->field_of_view / 2);
	i = 0;
	// TODO: is this even necessary
	while (i < raycaster->number_of_rays)
	{
		ray = &raycaster->rays[i];
		memset(ray, 0, sizeof(t_ray));
		ray->id = i;
		ray->map_pos.x = player->world_pos.x / 50.0f;
		ray->map_pos.y = player->world_pos.y / 50.0f;
		ray->frac_map_pos.x = player->world_pos.x / 50.0f;
		ray->frac_map_pos.y = player->world_pos.y / 50.0f;
		ray->angle_in_radians
			= raycaster->leftmost_ray_angle - (ray->id * raycaster->angle_increment);
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
		ray->map_pos.x = player->world_pos.x / 50.0f;
		ray->map_pos.y = player->world_pos.y / 50.0f;
		ray->frac_map_pos.x = player->world_pos.x / 50.0f;
		ray->frac_map_pos.y = player->world_pos.y / 50.0f;
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

	ray->dx = fabs(1 / ray->dir.x);
	ray->dy = fabs(1 / ray->dir.y);

	double	sideDistX, sideDistY;
	if (ray->dir.x < 0)
	{
		ray->x_step = -1;
		sideDistX = (ray->frac_map_pos.x - ray->map_pos.x) * ray->dx;
		(void)sideDistX;
	}
	else
	{
		ray->x_step = +1;
		sideDistX = (ray->map_pos.x + 1 - ray->frac_map_pos.x) * ray->dx;
		(void)sideDistX;
	}
	if (ray->dir.y < 0)
	{
		ray->y_step = -1;
		sideDistY = (ray->frac_map_pos.y - ray->map_pos.y) * ray->dy;
		(void)sideDistY;
	}
	else
	{
		ray->y_step = +1;
		sideDistY = (ray->map_pos.y + 1 - ray->frac_map_pos.y) * ray->dy;
		(void)sideDistY;
	}
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
		if (map->layout[ray->map_pos.y][ray->map_pos.x] == '1')
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
	/*t_vector_double	step;*/
	/*step = find_first_h_intersect(game, ray);*/
	/*check_horizontal(ray, map, step, player, game);*/ /*step = find_first_v_intersect(game, ray);*/ /*check_vertical(ray, map, step, player, game);*/
}

// TODO: correct perspective distance
void	get_shortest_distance(t_ray *ray, t_player *player, t_raycaster *rc)
{
	double	corrected_distance;

	// FIX: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// for some reason both horizontal and vertical intersections can't be found sometimes, !!!
	// leading me to mark both as infinity and we can't get a proper distance				!!!
	// not sure why, probably gotta implement proper DDA,									!!!
	// for now just use the previous' ray's distance so it doesn't look messed up,			!!!
	// plz fix soon!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (!ray->hit_vertical && !ray->hit_horizontal)
	{
		if (ray->id > 0)
		{
			ray->distance_to_h_wall = rc->rays[ray->id - 1].distance_to_h_wall;
			ray->distance_to_v_wall = rc->rays[ray->id - 1].distance_to_v_wall;
		}
	}

	if (ray->distance_to_h_wall < ray->distance_to_v_wall)
	{
		corrected_distance
			= (ray->distance_to_h_wall * cos(player->angle_in_radians - ray->angle_in_radians));
	}
	else
	{
		corrected_distance
			= (ray->distance_to_v_wall * cos(player->angle_in_radians - ray->angle_in_radians));
	}
	ray->distance_travelled = corrected_distance;
}

t_vector_double	find_first_h_intersect(t_game *game, t_ray *ray)
{
	const int				tile_width = game->tile_width;
	const int				tile_height = game->tile_height;
	const t_vector_double	world_pos = ray->world_pos;
	t_vector_double			step;

	if (ray->dir.y < 0)
	{
		ray->horizontal_intersect.y
			= floor(world_pos.y / tile_width) * tile_width - 1;
		step.y = -tile_height;
	}
	else
	{
		ray->horizontal_intersect.y
			= floor(world_pos.y / tile_width) * tile_width + tile_width;
		step.y = +tile_height;
	}
	ray->horizontal_intersect.x
		= world_pos.x + (world_pos.y - ray->horizontal_intersect.y) / tan(ray->angle_in_radians);
	step.x = tile_width * tan(ray->angle_in_radians);
	return (step);
}

t_vector_double	find_first_v_intersect(t_game *game, t_ray *ray)
{
	const int				tile_width = game->tile_width;
	const int				tile_height = game->tile_height;
	const t_vector_double	world_pos = ray->world_pos;
	t_vector_double			step;

	if (ray->dir.x < 0)
	{
		ray->vertical_intersect.x
			= floor(world_pos.x / tile_height) * tile_height - 1;
		step.x = -tile_width;
	}
	else
	{
		ray->vertical_intersect.x
			= floor(world_pos.x / tile_height) * tile_height + tile_height;
		step.x = +tile_width;
	}
	ray->vertical_intersect.y
		= world_pos.y + (world_pos.x - ray->vertical_intersect.x) * tan(ray->angle_in_radians);
	step.y = tile_height * tan(ray->angle_in_radians);
	return (step);
}

// TODO: check with parsed map
void	check_horizontal(t_ray *ray, t_map *map, t_vector_double step, t_player *player, t_game *game)
{
	bool			hit;
	t_vector_double	ray_pos;
	t_vector_int	check_map_pos;
	const double	ray_angle = ray->angle_in_radians;

	hit = false;
	ray_pos = ray->horizontal_intersect;
	while (!hit)
	{
		check_map_pos.x = ray_pos.x / game->tile_width;
		check_map_pos.y = ray_pos.y / game->tile_height;
		if (check_map_pos.x >= map->width || check_map_pos.x < 0
			|| check_map_pos.y >= map->height || check_map_pos.y < 0)
		{
			ray->distance_to_h_wall = INFINITY;
			return ;
		}
		if (map->layout[check_map_pos.y][check_map_pos.x] == '1')
		{
			hit = true;
			ray->hit_horizontal = true;
			ray->distance_to_h_wall
				= fabs(player->world_pos.x - ray_pos.x) / cos(ray_angle);
			double	adjacent = ray_pos.x - player->world_pos.x;
			double	opposite = ray_pos.y - player->world_pos.y;
			// TODO: use trig instead of pythagoras
			ray->distance_to_h_wall = sqrt((adjacent * adjacent) + (opposite * opposite));
			break ;
		}
		ray_pos.x += step.x;
		ray_pos.y += step.y;
	}
}

// TODO: check with parsed map
void	check_vertical(t_ray *ray, t_map *map, t_vector_double step, t_player *player, t_game *game)
{
	bool			hit;
	t_vector_double	ray_pos;
	t_vector_int	check_map_pos;
	const double	ray_angle = ray->angle_in_radians;

	hit = false;
	ray_pos = ray->vertical_intersect;
	while (!hit)
	{
		check_map_pos.x = ray_pos.x / game->tile_width;
		check_map_pos.y = ray_pos.y / game->tile_height;
		if (check_map_pos.x >= map->width || check_map_pos.x < 0 ||
			check_map_pos.y >= map->height || check_map_pos.y < 0)
		{
			ray->distance_to_v_wall = INFINITY;
			return;
		}
		if (map->layout[check_map_pos.y][check_map_pos.x] == '1')
		{
			hit = true;
			ray->hit_vertical = true;
			ray->distance_to_v_wall
				= fabs(player->world_pos.x - ray_pos.x) / cos(ray_angle);
			double	adjacent = ray_pos.x - player->world_pos.x;
			double	opposite = ray_pos.y - player->world_pos.y;
			// TODO: use trig instead of pythagoras
			ray->distance_to_v_wall = sqrt((adjacent * adjacent) + (opposite * opposite));
			break ;
		}
		ray_pos.x += step.x;
		ray_pos.y += step.y;
	}
}
