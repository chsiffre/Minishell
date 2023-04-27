/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/27 15:05:02 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			free(data->lst->content[i++]);
		free(data->lst);
		data->lst = next;
	}
	i = 0;
	while (data->result[i])
		free(data->result[i++]);
	data->i = 0;
}

void	ft_prompt(t_data *data)
{
	t_lst	*tmp;

	while (1)
	{
		data->line = readline("prompt> ");
		if (data->line)
			add_history(data->line);
		ft_parse(data);
		tmp = data->lst;
		while (tmp)
		{
			printf("%s\n", tmp->content[0]);
			ft_check_type(data, tmp);
			tmp = tmp->next;
		}
		free(data->line);
		ft_to_free(data);
	}
}
