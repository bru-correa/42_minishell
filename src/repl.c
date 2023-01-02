/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:04:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/02 11:17:58 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>

static void	print_cmds(t_cmd **cmds);
static void	print_args(char **args);
static void	print_rdir_list(t_slist **rdir_list);

void	repl(t_env_var **env_list)
{
	char		*input;
	t_pipeline	*pipeline;

	while (1)
	{
		input = readline(">$ ");
		add_history(input);
		pipeline = parse_input(input, env_list);
		free(input);
		if (pipeline == NULL)
			continue ;
		print_cmds(pipeline->cmds);
		if (ft_strncmp(pipeline->cmds[pipeline->cmd_index]->args[0],
				"exit", 5) == 0)
			repl_exit(pipeline, env_list);
		clear_pipeline(pipeline);
	}
}

// WARNING: Just for debug
static void	print_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
	{
		print_args(cmds[i]->args);
		print_rdir_list(cmds[i]->rdir_list);
		ft_printf("\n");
		i++;
	}
}

static void	print_args(char **args)
{
	int	i;

	ft_printf("Args:\n");
	if (args == NULL)
	{
		ft_printf("Empty\n");
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		ft_printf("`%s` ", args[i]);
		i++;
	}
	ft_printf("\n");
}

static void	print_rdir_list(t_slist **rdir_list)
{
	t_slist	*current;

	ft_printf("Redirects:\n");
	if (rdir_list == NULL)
	{
		ft_printf("Empty\n");
		return ;
	}
	current = *rdir_list;
	while (current != NULL)
	{
		ft_printf("`%s` ", current->data, current->type);
		current = current->next;
	}
	ft_printf("\n");
}
