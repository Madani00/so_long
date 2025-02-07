/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:44:10 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/06 22:31:06 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct stack_a
{
	int				data;
	struct stack_a	*next;
}	t_my_stack;

int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, int n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, char *src, size_t size);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strchr(char *s, int c);
char		*ft_strrchr(char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
long		ft_atoi(char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(char *s);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_error(char *s);
void		ft_putnbr_fd(int n, int fd);
int			ft_strcmp(char *s1, char *s2);

t_my_stack	*ft_lstnew(int content);
void		ft_lstadd_front(t_my_stack **lst, t_my_stack *new);
int			ft_lstsize(t_my_stack *lst);
t_my_stack	*ft_lstlast(t_my_stack *lst);
void		ft_lstadd_back(t_my_stack **lst, t_my_stack *new);
void		ft_lstdelone(t_my_stack *lst, int (*del)(int));
void		ft_lstclear(t_my_stack **lst, int (*del)(int));
void		ft_lstiter(t_my_stack *lst, int (*f)(int));
t_my_stack	*ft_lstmap(t_my_stack *lst, int (*f)(int), int (*del)(int));

#endif
