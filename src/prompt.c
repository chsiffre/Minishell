/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/12 13:58:39 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_to_free(t_lst *tmp, t_data *data)
{
	int	i;

	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
			free(tmp->content[i++]);
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	while (data->lst->next != NULL)
	{
		i = 0;
		while (data->lst->content[i])
			free(data->lst->content[i++]);
		free(data->lst);
		data->lst = data->lst->next;
	}
	i = 0;
	while (data->lst->content[i])
		free(data->lst->content[i++]);
	free(data->lst);
}

void	ft_prompt(t_data *data)
{
	t_lst	*tmp;

	while (1)
	{
		data->line = readline("prompt>");
		if (data->line)
			add_history(data->line);
		ft_parse(data);
		tmp = data->lst;
		printf("%s\n", tmp->content[0]);
		while (tmp)
		{
			ft_check_type(data, tmp);
			tmp = tmp->next;
		}
		free(data->line);
		ft_to_free(tmp, data);
	}
}
