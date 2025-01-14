/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:44:32 by kytan             #+#    #+#             */
/*   Updated: 2025/01/14 08:55:53 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <string.h>
#include <math.h>
#include "Player.h"
#include "Utils.h"
#include "Game.h"
#include "Map.h"
#include "Image.h"

void    parse_input(t_game *game, int argc, char **argv)
{
    validate_input(argc, argv);
}