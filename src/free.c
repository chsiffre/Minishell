/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/17 16:49:28 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*free_data(t_data *data)
{
	int	i;

	i = 0;
	i = 0;
	while (data->res_parse && data->res_parse[i])
	{
		if (data->res_parse[i])
			free(data->res_parse[i++]);
		else
			i++;
	}
	if (data->res_parse)
		free(data->res_parse);
	i = 0;
	while (data->res_split && data->res_split[i])
	{
		if (data->res_split[i])
			free(data->res_split[i++]);
		else
			i++;
	}
	if (data->res_split)
		free(data->res_split);
	return (NULL);
}

void	ft_to_free(t_data *data)
{
	int		i;
	t_lst	*next;

	next = NULL;
	while (data->iterator != NULL)
	{
		next = data->iterator->next;
		i = 0;
		while (data->iterator->content[i])
		{
			if (data->iterator->content[i])
				free(data->iterator->content[i++]);
		}
		free(data->iterator->content);
		free(data->iterator);
		data->iterator = next;
	}
	ft_close_end(data);
	data->in_redir = 0;
	data->out_redir = 0;
	data->i = 0;
	data->y = 0;
	data->ind = 0;
}
