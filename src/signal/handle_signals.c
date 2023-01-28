/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:28:30 by jramondo          #+#    #+#             */
/*   Updated: 2023/01/28 17:20:22 by jramondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_exit(int sig_num)
{

    ft_putchar_fd('\n',1);
    //Free_all(); Funcao para dar free em tudo que foi alocado e dar rl_clear_history.
    exit(sig_num);
}

void    sig_handle(int sig_num)
{
    (void)signum;
    //if() ira tratar com o heredoc fechando o arquivo e enviando error.
    //else if(p_id !=0) encerrar processos dando kill
    /*else
    {
        write(1, "\n",1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    */
   //ideal ter uma variavel para pegar o valor 130 indicando o sigterm.
}