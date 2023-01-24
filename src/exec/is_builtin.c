/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:50:17 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/23 20:55:43 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// TODO: Make ft_strcmp() function
int	is_builtin(char *cmd_name)
{
	if (cmd_name == NULL)
		return (FALSE);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}
