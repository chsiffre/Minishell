/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/12 13:17:04 by lucas            ###   ########.fr       */
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
		if (!data->line)
			return ;
		else if (data->line[0] != '\0')
			add_history(data->line);
		data->line = ft_pre_split(data->line);
		data->lst = ft_parse(data);
		while (data->lst && data->lst->content)
		{
			if (data->is_redir == 1)
			{
				ft_check_type(data);
				data->fd = 0;
				dup2(data->fd, STDOUT_FILENO);
				data->is_redir = 0;
			}
			else if (ft_check_type(data) == 1)
				break ;
			if (data->lst == NULL || data->lst->next == NULL)
				break ;
			data->lst = data->lst->next;
		}
		free(data->line);
		ft_to_free(data);
	}
}
