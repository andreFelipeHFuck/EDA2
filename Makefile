all:
	gcc main.c arvores/arvoreRubroNegra.c -o main
	echo "Arquivos compilados com sucesso"
run:
	./main
clean:
	