/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:45:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 23:49:43 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_invalid_var(char *name);

int	check_var_name(char *name)
{
	int	i;

	if (ft_isalpha(name[0]) == FALSE && name[0] != '_')
		return (FALSE);
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == FALSE && name[i] != '_' && name[i] != '=')
			return (print_invalid_var(name));
		i++;
	}
	return (TRUE);
}

static int	print_invalid_var(char *name)
{
	ft_putstr_fd("mini$HELL: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
