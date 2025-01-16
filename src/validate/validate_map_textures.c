/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:30:55 by kytan             #+#    #+#             */
/*   Updated: 2025/01/16 14:54:15 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Error.h"
#include "libft.h"

#define TOTAL_TEXTURE_ELEMENTS 6
#define IS_FILLED 1
#define NOT_FILLED 0

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

    if (!nline)
        return (0);
    line = ft_strtrim(nline, "\n ");
    free(nline);
    return (ft_strtok(line, " "));
}

int textures_filled(char **textures)
{
    int     i;

    i = 0;
    while (i < TOTAL_TEXTURE_ELEMENTS)
        if (!textures[i++])
            return (NOT_FILLED);
    return (IS_FILLED);
}

// 1 COND: IF EOF IS REACHED
//      BREAK OUT OF LOOP
//      CHECK IF ALL TEXTURES ARE FILLED
//          IF ALL TEXTURES ARE NOT FILLED
//              PRINT ERROR AND EXIT
//          IF ALL TEXTURES ARE FILLED
//              CHECK AND VALIDATE TEXTURE FILE PATHS
//              IF TEXTURE FILE PATH IS VALID
//                  RETURN (SUCCESS)
//              IF TEXTURE FILE PATH IS INVALID
//                  RETURN (FAILURE)
// 2 COND: IF TEXT IS FILLED BEFORE EOF IS REACHED
//      SAME THUNG
//      



int validate_map_textures(char *file, int fd)
{
    char    *id_token;
    char    *line;
    char    **textures;

    textures = ft_calloc(TOTAL_TEXTURE_ELEMENTS, sizeof(char *));
    while (!textures_filled(textures))
    {
        line = get_next_line(fd);
        if (!line)
            return (std);
        id_token = parse_token(line);
    //     if (!id_token)
    //         break ;
    //     if (valid_id_token && )
    //     if (ft_strcmp("NO", id_token))
    //         if (parse_north_txt(textures, line))
    //             return (clean_free() && stderr_msg());
    //     else if (ft_strcmp("SO", id_token))
    //         if (parse_south_txt(textures, line))
    //             return (clean_free() && stderr_msg());
    //     else if (ft_strcmp("WE", id_token))
    //         if (parse_west_txt(textures, line))
    //             return (clean_free() && stderr_msg());
    //     else if (ft_strcmp("EA", id_token))
    //         if (parse_west_txt(textures, line))
    //             return (clean_free() && stderr_msg());
    //     else if (ft_strcmp("F", id_token))
    //         if (parse_floor_txt(textures, line))
    //             return (clean_free() && stderr_msg());
    //     else if (ft_strcmp("C", id_token))
    //         if (parse_ceiling_txt(textures, line))
    //             return (clean_free() && stderr_msg());
    //     free(id_token);
    }
    // if ()
    //     ;
}