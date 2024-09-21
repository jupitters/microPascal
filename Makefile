
all:
gcc -c -g -Wall -lm -fPIC src/io.c -o src/io.o; gcc -c -g -Wall -lm -fPIC src/lexer.c -o src/lexer.o; gcc -c -g -Wall -lm -fPIC src/main.c -o src/main.o; gcc -c -g -Wall -lm -fPIC src/microPascal.c -o src/microPascal.o; gcc -c -g -Wall -lm -fPIC src/token.c -o src/token.o; gcc src/io.o src/lexer.o src/main.o src/microPascal.o src/token.o -g -Wall -lm -fPIC -o a;

clean:
  rm src/*.o; rm .\a.exe;
  
exe:
.\a.exe .\examples\main.mp