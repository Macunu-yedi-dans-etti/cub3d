/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:22:19 by musoysal          #+#    #+#             */
/*   Updated: 2025/09/27 19:58:19 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/cub3d.h"
#include <fcntl.h>
#ifndef O_DIRECTORY
#define O_DIRECTORY 00200000
#endif

//dosya geçerli mi? // is_dir
//dosya uzantısı .cub mi?
//dosya okunabilir mi?
//dosysa .xpm dosyaları geçerli mi?


static int is_cub_extension(const char *filename)
{
    int len = ft_strlen(filename);
    return (len > 4 && filename[len - 4] == '.' &&
            filename[len - 3] == 'c' &&
            filename[len - 2] == 'u' &&
            filename[len - 1] == 'b');
}
static int is_xpm_extension(const char *filename)
{
    int len = ft_strlen(filename);
    return (len > 4 && filename[len - 4] == '.' &&
            filename[len - 3] == 'x' &&
            filename[len - 2] == 'p' &&
            filename[len - 1] == 'm');
}

static int is_directory(const char *path)
{

    // open kullan
    int fd = open(path, O_DIRECTORY);
    if (fd != -1)
    {
        close(fd);
        return (1); // dizin
    }
    return (0); // dosya
}

int file_control(char *file_path, int fd)
{
    if (is_directory(file_path))
    {
        ft_error("Invalid file type. Expected a file\n");
        return (0);
    }
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        ft_error("Cannot open file\n");
        return (0);
    }
    close(fd);
    
    if (is_cub_extension(file_path) == 0)
    {
        ft_error("Invalid file extension. Expected .cub\n");
        return (0);
    }
    if (is_xpm_extension(file_path) == 0)
    {
        ft_error("Invalid file extension. Expected .xpm\n");
        return (0);
    }
    return (1);
}
