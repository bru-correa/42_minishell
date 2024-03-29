/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:50:17 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 01:26:08 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (cmd_name == NULL)
		return (FALSE);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (TRUE);
	return (FALSE);
}
