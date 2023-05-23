/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:07:10 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/23 15:14:50 by luhumber         ###   ########.fr       */
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
	if (data->in_redir > 0)
		dup2(data->savestdin, STDIN_FILENO);
	if (data->out_redir > 0)
		dup2(data->savestdout, STDOUT_FILENO);
	data->in_redir = 0;
	data->out_redir = 0;
	data->i = 0;
	data->y = 0;
}

void	ft_prompt(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		signal(SIGINT, ft_ctrl);
		signal(SIGTERM, ft_ctrl);
		signal(SIGQUIT, ft_ctrl);
		data->line = readline("prompt> ");
		while (data->line[i++])
			if (!ft_isascii(data->line[i]))
				ft_error(data, "non printable\n", 1);
		//data->line = "export TEST TEST2 TEST3";
		if (!data->line)
		{
			printf("exit\n");
			return ;
		}
		else if (data->line[0] != '\0')
			add_history(data->line);
		data->line = ft_pre_split(data->line);
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
