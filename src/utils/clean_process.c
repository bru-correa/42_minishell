/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:37:48 by jramondo          #+#    #+#             */
/*   Updated: 2023/01/31 15:01:58 by jramondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clean_process(void)
{
    int fd;

    fd = open(HDOC_TMPFILE, O_RDONLY | O_CREAT);
    if (fd < 0)
        return ;
    while (fd > STDERR_FILENO)
        close(fd--);
    unlink(HDOC_TMPFILE);
}