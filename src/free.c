/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/04 10:01:36 by charles          ###   ########.fr       */
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
		free(data->res_parse[i++]);
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
	while (data->lst != NULL)
	{
		i = 0;
		while (data->lst->content[i])
		{
			free(data->lst->content[i]);
			i++;
		}
		next = data->lst->next;
		free(data->lst->content);
		free(data->lst);
		data->lst = next;
	}
	ft_close_end(data);
	data->in_redir = 0;
	data->out_redir = 0;
	data->i = 0;
	data->y = 0;
	data->ind = 0;
}