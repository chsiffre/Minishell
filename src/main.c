/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/05/10 12:55:17 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_ctrl(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGTERM)
		exit (1);
	else
		return ;
}

void	ft_ctrl_fork(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
	}
	else if (signal == SIGTERM)
		exit (1);
	else
		return ;
}

void	ft_get_env(t_data *data)
{
	while (data->env_path)
	{
		if (ft_strnstr(*data->env_path, "PATH", 5))
		{
			data->path = *data->env_path + 5;
			data->split_path = ft_split(data->path, ':');
			if (!data->split_path)
				exit (1);
			return ;
		}
		data->env_path++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)**argv;
	ft_init_data(&data, envp);
	data = ft_init_struct(data);
	ft_get_env(&data);
	ft_prompt(&data);
	return (0);
}
