/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:56:03 by kytan             #+#    #+#             */
/*   Updated: 2025/01/14 16:18:54 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Player.h"
#include "Utils.h"
#include <stdio.h>
#include <mlx.h>
#include <string.h>
#include "Game.h"
#include "Map.h"
#include "Image.h"
#include "libft.h"
#include "Error.h"


void    validate_input(int argc, char **argv)
{
    if (argc > 1)
        return (stderr_msg(E_TOO_MANY_ARGS, 0) && shut_down(0, 0));
    if (validate_file(argv[1]))
        return (stderr_msg(E_INVALID_FILE, argv[1]));
    if (validate_map_elements(argv[1]))
        return (stderr_msg(E_INVALID_MAP_ELEMENTS, argv[1]) && shut_down(0, 0));
}
