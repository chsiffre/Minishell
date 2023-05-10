/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/10 10:26:43 by luhumber         ###   ########.fr       */
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
	data->y = 0;
}

void	ft_prompt(t_data *data)
{
	while (1)
	{
		signal(SIGINT, ft_ctrl);
		signal(SIGTERM, ft_ctrl);
		signal(SIGQUIT, ft_ctrl);
		data->line = readline("prompt> ");
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
