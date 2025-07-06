/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:47 by hanjkim           #+#    #+#             */
/*   Updated: 2024/09/14 18:53:07 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <limits.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# define BUFFER_SIZE 1024

//Client-side
void	send_string_to_server(const char *str, pid_t pid);
void	send_char_to_server(char c, pid_t pid);
void	handle_signal_client(int sig);
void	set_signal_client(void);

//Server-side
void	process_character(pid_t pid, int *index, char *current_char, int *bit);
void	handle_signal_server(int sig, siginfo_t *info, void *context);
void	set_signal_server(void (*handler)(int, siginfo_t *, void *));

#endif
