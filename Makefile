# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarratt <jbarratt@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 09:15:50 by jbarratt          #+#    #+#              #
#    Updated: 2025/05/23 11:38:40 by jbarratt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
REPO = git@vogsphere.42berlin.de:vogsphere/intra-uuid-4305e101-1b11-473a-8387-7b65c074a983-6573661-jbarratt

SHELL := /bin/bash
HEAD = $(addsuffix .h, $(NAME))

CC = cc -g
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iinclude
LFLAGS = -Llib -lft
AR = ar rcs
RM = rm -f
LN = ln -s -f

FILES =	server client

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): server client

server: server.c $(HEAD) include/libft.h lib/libft.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $< $(LFLAGS) -o $@

client: client.c $(HEAD) include/libft.h lib/libft.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $< $(LFLAGS) -o $@

# $(HEAD): $(SRCS) $(NAME)_stub.h include/libft.h
# 	[[ -f $(HEAD) ]] || cat $(NAME)_stub.h <(echo '#endif') > $(HEAD) 
# 	cproto -Iinclude -F"int\tf(a, b)" $(SRCS) | \
# 		sed -E 's/^([a-z_]+) /\1\t/' | \
# 		sed 's/^int\t/int\t\t/' | \
# 		grep -v 'main(' > $(NAME)_proto.h
# 	cat $(NAME)_stub.h $(NAME)_proto.h <(echo '#endif') > $(HEAD)
# 	sed -i 's/$(NAME)_stub\.h/$(HEAD)     /' $(HEAD)
# 
include/libft.h: libft/libft.h
	mkdir -p include
	$(LN) ../libft/libft.h include/libft.h

libft/libft.h:
	git clone https://github.com/jbarratt42/libft.git

lib/libft.a: libft/libft.h
	make -C libft
	mkdir -p lib
	$(LN) ../libft/libft.a lib/libft.a

clean:
	make -C libft clean
	$(RM) $(OBJS)
	$(RM) -r lib include

fclean: clean
	make -C libft fclean
	$(RM) server client

re: clean all

list:
	@echo $(SRCS)

libft:
	git clone https://github.com/jbarratt42/libft.git libft

repo: $(SRCS) $(HEAD) Makefile libft
	[[ ! -z $(REPO) ]]
	rm -rf $(HOME)/repo/$(NAME)/
	rm -f repo
	git clone $(REPO) $(HOME)/repo/$(NAME)
	ln -s $(HOME)/repo/$(NAME) repo
	cp $(SRCS) $(HEAD) Makefile repo
	cp -r libft repo && rm -rf repo/libft/.git
	sed -E '/^\$$\(HEAD\): /,/^$$/ s/^/# /' -i repo/Makefile
	cd repo && git add . && git commit && git push

test_repo: repo
	[[ ! -z "$(REPO)" ]]
	rm -rf $(HOME)/repo/$(NAME)/
	rm -f repo
	git clone $(REPO) $(HOME)/repo/$(NAME)
	ln -s $(HOME)/repo/$(NAME) repo
	ls -lR repo/
	cd repo && \
		norminette && \
		make && make clean && make fclean && \
		make $(NAME) && make re && make fclean && \
		make all

.PHONY: all clean fclean re debug list test_repo
