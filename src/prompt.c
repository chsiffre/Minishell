/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/12 10:57:02 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lsize(t_lst *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	ft_list_to_tab(t_data *data, t_lst *lst)
{
	t_lst	*tmp;
	int		i;
	int		j;

	tmp = lst;
	i = 0;
	data->cmd = malloc(sizeof(char *) * (ft_lsize(tmp) + 1));
	while (tmp)
	{
		j = 0;
		data->cmd[i] = malloc(sizeof(char) * ft_strlen((*tmp->content)));
		while (tmp->content[j])
		{
			data->cmd[i][j] = (*tmp->content[j]);
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	data->cmd[i] = NULL;
}

void	ft_lstdelo(t_lst *lst)
{
	if (lst)
	{
		free(lst->content);
		free(lst);
	}
}

void	ft_prompt(t_data *data)
{
	while (1)
	{
		data->line = readline("prompt>");
		if (data->line)
			add_history(data->line);
		ft_parse(data);
		while (data->lst)
		{
			ft_check_type(data);
			data->lst = data->lst->next;
		}
		free(data->line);
	}
}
