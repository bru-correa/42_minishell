/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 05:06:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 05:24:22 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_color_red(void);
static void	set_color_yellow(void);
static void	reset_color(void);
static void	print_div(void);

void	welcome(t_env_var **env_list)
{
	char	*user;

	user = search_env_var(env_list, "USER");
	if (ft_strncmp(user, "", 1) == 0)
		user = "UNKNOWN";
	set_color_red();
	print_div();
	set_color_yellow();
	ft_printf("   %s is entering The Domains of $HELL\n", user);
	set_color_red();
	print_div();
	reset_color();
	free(user);
}

static void	set_color_red(void)
{
	ft_printf("\033[0;31m");
}

static void	set_color_yellow(void)
{
	ft_printf("\033[0;33m");
}

static void	reset_color(void)
{
	ft_printf("\033[0m");
}

static void	print_div(void)
{
	ft_printf("=======================================================\n");
}
