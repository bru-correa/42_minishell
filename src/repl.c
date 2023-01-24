/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:04:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/23 22:59:30 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

static char			*prompt(t_env_var **env_list);
static t_pipeline	*read_input(char *input, t_env_var **env_list);

void	repl(t_env_var **env_list)
{
	char		*input;
	t_pipeline	*pipeline;

	while (1)
	{
		input = prompt(env_list);
		if (input == NULL)
			break ;
		pipeline = read_input(input, env_list);
		if (pipeline == NULL)
			continue ;
		execute(pipeline, env_list);
		clear_pipeline(pipeline);
	}
	clear_history();
}

// TODO: Do a prettier prompt
static char	*prompt(t_env_var **env_list)
{
	char	*input;

	input = readline("$> ");
	if (input == NULL)
	{
		clear_env_list(env_list);
		return (NULL);
	}
	add_history(input);
	return (input);
}

static t_pipeline	*read_input(char *input, t_env_var **env_list)
{
	t_pipeline	*pipeline;

	pipeline = parse_input(input, env_list);
	free(input);
	return (pipeline);
}
