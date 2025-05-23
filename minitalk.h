/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarratt <jbarratt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:57:52 by jbarratt          #+#    #+#             */
/*   Updated: 2025/05/12 12:16:41 by jbarratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <unistd.h>
# include "libft.h"

/* server.c */
void	handler(int signal, siginfo_t *info, void *ucontext);
/* client.c */
void	send_bit(int pid, int b);
void	send_char(int pid, char c);
void	ack(int signal);
#endif
