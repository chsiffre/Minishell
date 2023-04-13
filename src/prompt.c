/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsiffre <chsiffre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/13 17:04:35 by chsiffre         ###   ########.fr       */
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
	while (1)
	{
		//data->line = readline("prompt>");
		data->line = " >out2 >in3 > out ls -l -a | >> outtt <in > out cat Makefile";
		data->line = ft_pre_split(data->line);
		if (!data->line)
			return ;
		else
			add_history(data->line);
		list = ft_parse(data);
		exit(1);
		while (list)
			list = list->next;	
		//free(data->line);
		//ft_free(data);
	}
}
