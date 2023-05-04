/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/04 16:01:29 by lucas            ###   ########.fr       */
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
	data->i = 0;
}

void	ft_prompt(t_data *data)
{
	while (1)
	{
		data->line = readline("prompt>");
		//data->line = "cat Makefile | ls > out";
		if (!data->line)
			return ;
		else
			add_history(data->line);
		data->lst = ft_parse(data);
		while (data->lst && data->lst->content)
		{
			if (ft_check_type(data) == 1)
				break ;
			if (data->lst == NULL || data->lst->next == NULL)
				break ;
			data->lst = data->lst->next;
		}
		free(data->line);
		ft_to_free(data);
	}
}
