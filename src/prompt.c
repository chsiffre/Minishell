/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/03 14:51:03 by chsiffre         ###   ########.fr       */
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
	t_lst *list;
	
	list = NULL;
	int i = 0;
	while (1)
	{
		//data->line = readline("prompt>");
		data->line = "cat Makefile | ls > out";
		if (!data->line)
			return ;
		else
			add_history(data->line);
		data->line = ft_pre_split(data->line);
		data->res_split = ft_split_charset(data->line, " \t\n\r\v\f");
		list = ft_parse(data);
		while (list)
		{
			printf("[%s]", list->content[i++]);
			printf("\n");
			list = list->next;
		}
		exit(1);
		//free(data->line);
		//ft_free(data);
	}
}
