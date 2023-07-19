/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:12:27 by luhumber          #+#    #+#             */
/*   Updated: 2023/07/19 13:28:53 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i])
			free(cmd[i]);
	}
	if (cmd)
		free(cmd);
}

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
	while (data->lst != NULL)
	{
		next = data->lst->next;
		i = 0;
		while (data->lst->content[i])
		{
			if (data->lst->content[i])
				free(data->lst->content[i++]);
		}
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
