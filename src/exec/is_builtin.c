/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:50:17 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/12 01:03:26 by jramondo         ###   ########.fr       */
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
	return (FALSE);
}
