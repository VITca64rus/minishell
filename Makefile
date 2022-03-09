all:
	make -C libft
	gcc *.c libft/libft.a -ltermcap -lreadline
clean:
	make clean -C libft