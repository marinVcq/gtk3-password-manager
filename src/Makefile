CC = gcc
CFLAGS = -Wall -g
LIBS = `pkg-config --cflags --libs gtk+-3.0` -lsqlite3
SRC = main.c myapp.c loginwindow.c authenticatedwindow.c
OUT = mygtkapp

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LIBS)

clean:
	rm -f $(OUT)

