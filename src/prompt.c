/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/03 14:57:51 by lucas            ###   ########.fr       */
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
