/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:30:30 by kytan             #+#    #+#             */
/*   Updated: 2025/01/14 16:47:32 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Error.h"

int validate_map_elements(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    validate_map_textures(file, fd);
    validate_map_layout(file, fd);
    close(fd);
}