/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:59:29 by jramondo          #+#    #+#             */
/*   Updated: 2023/02/12 01:54:28 by jramondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	argcount(char **args)
{
	int	argc;
	
	argc = 0;
	while (args[argc] != NULL)
		argc++;
	return(argc - 1);
}

static void	update_pwd_envs(t_env_var **env_list)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_var_to_env(env_list, "OLDPWD", search_env_var(env_list, "PWD"));
	add_var_to_env(env_list, "PWD", pwd);
	free((char *)pwd);
}

int	cd(char **args, t_env_var **env_list)
{
	char	*path;
	int			argc;

	argc = argcount(args);
	if (argc > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (args[1] == NULL)
		path = search_env_var(env_list, "HOME");
	else
		path = args[1];
	printf("%s\n",path);// teste para ver se o path vai certo
	if ((chdir(path) == -1))
	{
		perror("error");
		return (1);
	}
	update_pwd_envs(env_list);
	free((char *)path);
	return (0);
}