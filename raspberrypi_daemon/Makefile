
all:
	gcc -o server main.c server.c serial.c logger.c -L./libwebsockets/build/lib -lwebsockets

test:
	gcc test.c -L./libwebsockets/build/lib -lwebsockets
