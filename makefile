compile: compclient compserver
compclient: basic_client.o pipe_networking.o
	gcc -o run_client basic_client.o pipe_networking.o

compserver: basic_server.o pipe_networking.o
	gcc -o run_server basic_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

server:
	@./run_server
client:
	@./run_client

clean:
	rm *.o
	rm *~
