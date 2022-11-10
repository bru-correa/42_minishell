/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:24:46 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/10 17:57:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_hashtable(t_hashtable *table);

int	main(void)
{
	t_hashtable	*table;
	char		*home_dir;

	table = create_hashtable(HT_SIZE);
	ht_insert(table, "HOME", "/home/hellgardh/");
	ht_insert(table, "SHELL", "/usr/bin/zsh");
	print_hashtable(table);
	home_dir = ht_search(table, "HOME");
	ft_printf("Search: %s\n", home_dir);
	free_hashtable(table);
	return (0);
}

static void	print_hashtable(t_hashtable *table)
{
	int			i;
	t_ht_item	*item;

	i = 0;
	while (i < HT_SIZE)
	{
		item = table->items[i];
		if (item == NULL)
			ft_printf("%d | NULL\n", i);
		else
			ft_printf("%d | %s | %s\n", i, item->key, item->value);
		i++;
	}
}
