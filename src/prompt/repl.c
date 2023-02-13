/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:04:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 05:33:49 by bcorrea-         ###   ########.fr       */
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
		sig_setup_prompt();
		input = prompt(env_list);
		if (input == NULL)
			break ;
		pipeline = read_input(input, env_list);
		if (pipeline == NULL)
			continue ;
		execute(pipeline, env_list);
		clear_pipeline(pipeline);
	}
	rl_clear_history();
}

// TODO: Create a new prompt
static char	*prompt(t_env_var **env_list)
{
	char	*input;
	
	(void)env_list;
	input = readline("/-> ");
	if (input == NULL)
	{
		input = ft_strdup("exit");
		ft_printf("exit\n");
		return (input);
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