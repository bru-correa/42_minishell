/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:16:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/10 17:57:24 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ht_item	*create_ht_item(char *key, char *value)
{
	t_ht_item	*item;

	item = malloc(sizeof(t_ht_item));
	if (item == NULL)
		return (NULL);
	item->key = ft_strdup(key);
	if (item->key == NULL)
	{
		free(item);
		return (NULL);
	}
	item->value = ft_strdup(value);
	if (item->value == NULL)
	{
		free(item);
		free(key);
		return (NULL);
	}
	return (item);
}

t_hashtable	*create_hashtable(int size)
{
	t_hashtable	*table;
	int			i;

	table = malloc(sizeof(t_hashtable));
	if (table == NULL)
		return (NULL);
	table->size = size;
	table->count = 0;
	table->items = ft_calloc(table->size, sizeof(t_ht_item*));
	if (table->items == NULL)
	{
		free(table);
		return (NULL);
	}
	i = 0;
	while (i < table->size)
	{
		table->items[i] = NULL;
		i++;
	}
	return (table);
}

void	free_ht_item(t_ht_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	free_hashtable(t_hashtable *table)
{
	int			i;
	t_ht_item	*item;

	i = 0;
	while (i < table->size)
	{
		item = table->items[i];
		if (item != NULL)
			free_ht_item(item);
		i++;
	}
	free(table->items);
	free(table);
}

// TODO: Needs a better hash function
int	hash(char *str)
{
	unsigned long	hashval;
	int				i;

	hashval = 0;
	i = 0;
	while (str[i])
	{
		hashval += str[i];
		i++;
	}
	return (hashval % HT_SIZE);
}

void	ht_insert(t_hashtable *table, char *key, char *value)
{
	t_ht_item	*item;
	int			index;

	item = create_ht_item(key, value);
	if (item == NULL)
	{
		ft_putstr_fd("Error: Could not create env_var!\n", STDERR_FILENO);
		return ;
	}
	index = hash(key);
	if (table->items[index] == NULL)
	{
		if (table->count == table->size)
		{
			ft_putstr_fd("Error: env_vars is full!\n", STDERR_FILENO);
			free(item);
			return ;
		}
		table->items[index] = item;
		table->count++;
	}
}

char	*ht_search(t_hashtable *table, char *key)
{
	int			index;
	t_ht_item	*item;

	index = hash(key);
	item = table->items[index];
	if (item != NULL)
	{
		if (ft_strncmp(key, item->key, ft_strlen(key)) == 0)
			return (item->value);
	}
	return (NULL);
}
