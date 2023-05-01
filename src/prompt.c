/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/01 22:38:52 by lucas            ###   ########.fr       */
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
	while (1)
	{
		data->line = readline("prompt> ");
		if (!data->line)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->line);
		ft_parse(data);
		while (data->lst && data->lst->content)
		{
			if (ft_check_type(data) == 1)
				break ;
			data->lst = data->lst->next;
		}
		free(data->line);
		ft_to_free(data);
	}
}
