/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goodbye.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 05:30:09 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 05:34:45 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_color_red(void);
static void	set_color_green(void);
static void	reset_color(void);
static void	print_div(void);

void	goodbye(t_env_var **env_list)
{
	char	*user;

	user = search_env_var(env_list, "USER");
	if (ft_strncmp(user, "", 1) == 0)
		user = "UNKNOWN";
	set_color_red();
	print_div();
	set_color_green();
	ft_printf("   %s escaped from $HELL... for now\n", user);
	set_color_red();
	print_div();
	reset_color();
	free(user);
}

static void	set_color_red(void)
{
	ft_printf("\033[0;31m");
}

static void	set_color_green(void)
{
	ft_printf("\033[0;32m");
}

static void	reset_color(void)
{
	ft_printf("\033[0m");
}

static void	print_div(void)
{
	ft_printf("=======================================================\n");
}
