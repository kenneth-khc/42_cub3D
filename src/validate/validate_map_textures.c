/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:30:55 by kytan             #+#    #+#             */
/*   Updated: 2025/01/16 17:22:17 by kytan            ###   ########.fr       */
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

char    *parse_token(char *nline)
{
    char    *line;

    if (!nline)
        return (0);
    line = ft_strtrim(nline, "\n ");
    free(nline);
    return (ft_strtok(line, " "));
}

char    *new_token(char *line)
{
    char    *ptr;

    if (!line)
        return (0);
    ptr = line;
    line = ft_strtrim(line, " \n");
    free(ptr);
    return (ft_strtok(line, " "));
}

/**
 * @return the texture asset path represented as a string;
 * @return NULL if there's no token after `id_token` OR
 * @return if token is an invalid texture path
 */
char    *valid_texture(char *texture_token)
{
    if (!texture_token)
        return (0);
    if (valid_texture_path(texture_token))
        return (texture_token);
    free(texture_token);
    return (0);
}

int validate_map_textures(char *file, int fd)
{
    char    *id_token;
    char    *line;
    char    **textures;

    textures = ft_calloc(TOTAL_TEXTURE_ELEMENTS, sizeof(char *));
    while (!textures_filled(textures)) // COND 1: TEXTURES ARE NOT FULL
    {
        line = get_next_line(fd); // COND 2: EOF NOT REACHED
        if (!line) 
            break ;
        id_token = new_token(line); //tokenize line
        if (valid_id(id_token) != -1) // valid_id() returns an index of 0 to 5 if its a valid index token if not it returns -1
            textures[valid_id(id_token)] = valid_texture(new_token(line)); //valid_texture returns 0 if 1. theres no token after id_token 2. the token is not a valid path
        free(line);
    }
    if (!textures_filled(textures))
        return (stderr_msg(E_TEXTURE_ELEMENT));
    return (validate_texture_paths(textures));
}