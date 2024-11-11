/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:38:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/11 20:57:55 by kecheong         ###   ########.fr       */
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

void	init_raycaster(t_raycaster *raycaster, t_player *player, t_game *game)
{
	int	i;

	raycaster->number_of_rays = game->screen_width;
	i = 0;
	while (i < raycaster->number_of_rays)
	{
		memset(&raycaster->rays[i], 0, sizeof(t_ray));
		raycaster->rays[i].id = i;
		i++;
	}
	raycaster->angle_increment = player->field_of_view / raycaster->number_of_rays;
	// TODO: are these angles correct?
	raycaster->leftmost_ray_angle = player->angle_in_radians + (player->field_of_view / 2);
	raycaster->rightmost_ray_angle = player->angle_in_radians - (player->field_of_view / 2);
}

void	check_horizontal(t_ray *ray, t_map *map, double x_step, double y_step, t_player *player, double angle)
{(void)map;
	bool			hit;
	t_vector_double	ray_pos;
	t_vector_int	check_map_pos;

	hit = false;
	ray_pos = ray->horizontal_intersect;
	while (!hit)
	{
		check_map_pos.x = ray_pos.x / 64;
		check_map_pos.y = ray_pos.y / 64;
		if (check_map_pos.x > 9 || check_map_pos.x < 0 ||
			check_map_pos.y > 9 || check_map_pos.y < 0)
		{
			ray->distance_to_h_wall = INFINITY;
			return ;
		}
		if (g_layout[check_map_pos.y][check_map_pos.x] == '1')
		{
			hit = true;
			ray->distance_to_h_wall = fabs(player->world_pos.x - ray_pos.x) / cos(angle);
			ray->distance_to_h_wall = ray->distance_to_h_wall * cos(player->angle_in_radians - angle);
			/*printf("FOUND H DISTANCE: %f\n", ray->distance_to_h_wall);*/
			break ;
		}
		if (ray_pos.x > 0)
			ray_pos.x += x_step;
		if (ray_pos.y > 0)
			ray_pos.y += y_step;
	}
}

void	check_vertical(t_ray *ray, t_map *map, double x_step, double y_step, t_player *player, double angle)
{(void)map;
	bool			hit;
	t_vector_double	ray_pos;
	t_vector_int	check_map_pos;

	hit = false;
	ray_pos = ray->vertical_intersect;
	while (!hit)
	{
		check_map_pos.x = ray_pos.x / 64;
		check_map_pos.y = ray_pos.y / 64;
		if (check_map_pos.x > 9 || check_map_pos.x < 0 ||
			check_map_pos.y > 9 || check_map_pos.y < 0)
		{
			ray->distance_to_v_wall = INFINITY;
			return;
		}
		if (g_layout[check_map_pos.y][check_map_pos.x] == '1')
		{
			hit = true;
			ray->distance_to_v_wall = fabs(player->world_pos.x - ray_pos.x) / cos(angle);
			ray->distance_to_v_wall = ray->distance_to_v_wall * cos(player->angle_in_radians - angle);
			/*printf("FOUND V DISTANCE: %f\n", ray->distance_to_v_wall);*/
			break ;
		}
		ray_pos.x += x_step;
		ray_pos.y += y_step;
	}
}

/* Send forth a ray until it hits a wall. Behold, my wizard casting powers */
void	cast(t_ray *ray, double angle, t_player *player, t_map *map, t_game *game)
{(void)game;
	t_vector_double	world_pos;
	t_vector_double	dir;

	world_pos = player->world_pos;
	dir.x = cos(angle);
	dir.y = -sin(angle);
	double	y_step;
	double	x_step;

	if (dir.y < 0)
	{
		ray->horizontal_intersect.y = floor(world_pos.y / 64) * (64) - 1;
		y_step = -64;
	}
	else
	{
		ray->horizontal_intersect.y = floor(world_pos.y / 64) * 64 + 64;
		y_step = 64;
	}

	/*if (angle == M_PI / 2 || angle == 0)*/
	/*{*/
	/*	printf("OMG\n");*/
	/*	ray->horizontal_intersect.x = world_pos.x;*/
	/*	x_step = 0;*/
	/*}*/
	/*else*/
	/*{*/
		ray->horizontal_intersect.x = world_pos.x + (world_pos.y - ray->horizontal_intersect.y) / tan(angle);
		x_step = 64 / tan(angle);
	/*}*/
	check_horizontal(ray, map, x_step, y_step, player, angle);
	fprintf(game->logfile, "Ray %d: H: %f", ray->id, ray->distance_to_h_wall);

	if (dir.x < 0)
	{
		ray->vertical_intersect.x = floor(world_pos.x / 64) * 64 - 1;
		x_step = -64;
	}
	else
	{
		ray->vertical_intersect.x = floor(world_pos.x / 64) * 64 + 64;
		x_step = 64;
	}
	/*if (angle == M_PI / 2 || angle == 0)*/
	/*{*/
	/*	printf("OMG\n");*/
	/*	ray->vertical_intersect.y = world_pos.y;*/
	/*	y_step = 0;*/
	/*}*/
	/*else*/
	/*{*/
		ray->vertical_intersect.y = world_pos.y + (world_pos.x - ray->vertical_intersect.x) * tan(angle);
		y_step = 64 * tan(angle);
	/*}*/
	check_vertical(ray, map, x_step, y_step, player, angle);
	fprintf(game->logfile, " V: %f\n", ray->distance_to_v_wall);
}

void	raycast(t_raycaster *raycaster, t_player *player, t_game *game)
{ (void)game;
	t_ray	*ray;

	/*
	// cast leftmost ray
	ray = &raycaster->rays[0];
	cast(ray, raycaster->leftmost_ray_angle - raycaster->angle_increment * ray->id,
		player, &game->map, game);
	// cast centre ray
	ray = &raycaster->rays[raycaster->number_of_rays / 2];
	cast(ray, raycaster->leftmost_ray_angle - raycaster->angle_increment * ray->id,
		player, &game->map, game);
	// cast rightmost ray
	ray = &raycaster->rays[raycaster->number_of_rays - 1];
	cast(ray, raycaster->leftmost_ray_angle- raycaster->angle_increment * ray->id,
		player, &game->map, game);
	*/
	init_raycaster(raycaster, &game->player, game);
	for (int x = 0; x < game->screen_width; x++)
	{
		ray = &raycaster->rays[x];
		cast(ray, raycaster->leftmost_ray_angle - raycaster->angle_increment * ray->id,
		player, &game->map, game);
	}
}
