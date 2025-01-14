/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:30:55 by kytan             #+#    #+#             */
/*   Updated: 2025/01/14 17:41:22 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Error.h"
#include "libft.h"

int parse_map_textures(char **textures, char *line)
{
    if texture already exists in textures[]
        error duplicate
    token = ft_strtok(line);
    if element identifier present but no texture follow
        error N/S/E/W/F/C texture not found
    
}

char    *parse_token(char *nline)
{
    char    *line;

    line = ft_strtrim(nline, "\n ");
    free(nline);
    return (ft_strtok(line, " "));
}

int validate_map_textures(char *file, int fd)
{
    char    *id_token;
    char    *textures[4];

    while (!textures_filled(textures))
    {
        id_token = parse_token(get_next_line(fd));
        if (!id_token)
            break ;
        if (ft_strcmp("NO", id_token))
            if (parse_north_txt(textures, line))
                return (clean_free() && stderr_msg());
        else if (ft_strcmp("SO", id_token))
            if (parse_south_txt(textures, line))
                return (clean_free() && stderr_msg());
        else if (ft_strcmp("WE", id_token))
            if (parse_west_txt(textures, line))
                return (clean_free() && stderr_msg());
        else if (ft_strcmp("EA", id_token))
            if (parse_west_txt(textures, line))
                return (clean_free() && stderr_msg());
        else if (ft_strcmp("F", id_token))
            if (parse_floor_txt(textures, line))
                return (clean_free() && stderr_msg());
        else if (ft_strcmp("C", id_token))
            if (parse_ceiling_txt(textures, line))
                return (clean_free() && stderr_msg());
        free(id_token);
    }
    

}