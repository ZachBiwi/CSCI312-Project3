Makefile:
all: ServerC Client
Client: Client.c Server.h
	cc -o client Client.c Server.h
ServerC: ServerC.c Server.h
	cc -o serverC ServerC.c Server.h
clean:
rm -f serverC
rm -f client
