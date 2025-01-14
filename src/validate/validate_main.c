/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:56:03 by kytan             #+#    #+#             */
/*   Updated: 2025/01/14 09:21:26 by kytan            ###   ########.fr       */
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
#include "Error.h"

#define FILE_EXTENSION_LEN 4

int non_cub_file(char *file)
{
    return (ft_strncmp(file + ft_strlen(file) - FILE_EXTENSION_LEN, ".cub"));
}

void    validate_input(int argc, char **argv)
{
    if (argc > 2)
        return (stderr_msg(E_TOO_MANY_ARGS, 0));
    if (non_cub_file(argv[1]))
        return (stderr_msg(E_CUB_FILETYPE, argv[1]));
    if ()
}