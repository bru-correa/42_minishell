/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:46:04 by jramondo          #+#    #+#             */
/*   Updated: 2023/02/02 20:57:36 by jramondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_dir(const char *cwd)
{
	char	**dir;
	char	*ret;
	int		i;

	i = -1;
	if (ft_strncmp(cwd, "/", 2) == 0)
		return (ft_strdup("/"));
	dir = ft_split(cwd, '/');
	while (dir[++i])
        {
		if (dir[i + 1] == NULL)
			ret = ft_strdup(dir[i]);
        }
    i = - 1;
	while(dir[++i] != NULL)
    {
        free(dir[i]);
    }
    free(dir);
	return (ret);
}

char	*handle_prompt(void)
{
	char	*prompt;
	char	cwd[PATH_MAX];

    prompt = "";
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		prompt = ft_strjoin(prompt, get_dir(cwd));
	prompt = ft_strjoin(prompt, "-> ");
	return (prompt);
}
