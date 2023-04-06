/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:20:17 by chsiffre          #+#    #+#             */
/*   Updated: 2023/04/06 13:49:04 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_ctrl(int signal)
{
	if (signal == 2)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)**argv;
	ft_init_data(&data, envp);
	ft_get_env(&data);
	data = ft_init_struct(data);	
	signal(SIGINT, ft_ctrl);
	ft_prompt(&data);
	return (0);
}
