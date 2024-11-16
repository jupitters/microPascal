
all:
gcc -c -g -Wall -lm -fPIC src/io.c -o src/io.o; gcc -c -g -Wall -lm -fPIC src/lexer.c -o src/lexer.o; gcc -c -g -Wall -lm -fPIC src/main.c -o src/main.o; gcc -c -g -Wall -lm -fPIC src/microPascal.c -o src/microPascal.o; gcc -c -g -Wall -lm -fPIC src/token.c -o src/token.o; gcc -c -g -Wall -lm -fPIC src/parser.c -o src/parser.o; gcc -c -g -Wall -lm -fPIC src/AST.c -o src/AST.o; gcc -c -g -Wall -lm -fPIC src/lista.c -o src/lista.o; gcc -c -g -Wall -lm -fPIC src/tipos.c -o src/tipos.o; gcc src/AST.o src/io.o src/lexer.o src/lista.o src/main.o src/microPascal.o src/parser.o src/tipos.o src/token.o -g -Wall -lm -fPIC -o a;

clean:
  rm src/*.o; rm .\a.exe;
  
exe:
.\a.exe .\examples\main.mp