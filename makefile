compile: compclient compserver comppersistentserver compforkingserver
compclient: basic_client.o pipe_networking.o
	@gcc -o run_client basic_client.o pipe_networking.o

compserver: basic_server.o pipe_networking.o
	@gcc -o run_server basic_server.o pipe_networking.o

comppersistentserver: persistent_server.o pipe_networking.o
	@gcc -o run_persistent_server persistent_server.o pipe_networking.o

compforkingserver: forking_server.o pipe_networking.o
	@gcc -o run_forking_server forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c -Wall

basic_server.o: basic_server.c pipe_networking.h
	@gcc -c basic_server.c -Wall

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c -Wall

persistent_server.o: persistent_server.c pipe_networking.h
	@gcc -c persistent_server.c -Wall

forking_server.o: forking_server.c pipe_networking.h
	@gcc -c forking_server.c -Wall

server:
	@./run_forking_server
client:
	@./run_client
pserver:
	@./run_persistent_server
regserver:
	@./run_server

clean:
	rm *.o
	rm *~
