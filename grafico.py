import matplotlib.pyplot as plt
import numpy as np
  
# create data
arquivoARN = open("assets/arvoreRubroNegra.txt", "r")
arquivoAVL = open("assets/arvoreAVL.txt", "r")
arquivoAB1 = open("assets/arvoreB1.txt", "r")
arquivoAB5 = open("assets/arvoreB5.txt", "r")
arquivoAB10 = open("assets/arvoreB10.txt", "r")
dadosARN = arquivoARN.read()
dadosAVL = arquivoAVL.read()

dadosAB1 = arquivoAB1.read()
dadosAB5 = arquivoAB5.read()
dadosAB10 = arquivoAB10.read()

yARN = dadosARN.split(";")
yAVL = dadosAVL.split(";")

yAB1 = dadosAB1.split(";")
yAB5 = dadosAB5.split(";")
yAB10 = dadosAB10.split(";")

tamanhoARN = len(yARN)
tamanhoAVL = len(yAVL)

tamanhoAB1 = len(yAB1)
tamanhoAB5 = len(yAB5)
tamanhoAB10 = len(yAB10)

i = 0
vetorInserirARNx = []
vetorInserirARNy = []
vetorRemoverARNx = []
vetorRemoverARNy = []

vetorInserirAVLx = []
vetorInserirAVLy = []
vetorRemoverAVLx = []
vetorRemoverAVLy = []

vetorInserirAB1x = []
vetorInserirAB1y = []

vetorInserirAB5x = []
vetorInserirAB5y = []

vetorInserirAB10x = []
vetorInserirAB10y = []

while i < tamanhoARN -1:
    split = yARN[i].split(":")
    if(split[0] == 'I'):
        vetorInserirARNx.append(int(split[1]))
        vetorInserirARNy.append(int(split[2]))
    else:
        vetorRemoverARNx.append(int(split[1]))
        vetorRemoverARNy.append(int(split[2]))
    i+=1

i = 0
while i < tamanhoAVL -1:
    split = yAVL[i].split(":")
    if(split[0] == 'I'):
        vetorInserirAVLx.append(int(split[1]))
        vetorInserirAVLy.append(int(split[2]))
    else:
        vetorRemoverAVLx.append(int(split[1]))
        vetorRemoverAVLy.append(int(split[2]))
    i+=1

i = 0
while i < tamanhoAB1 -1:
    split = yAB1[i].split(":")
    if(split[0] == 'I'):
        vetorInserirAB1x.append(int(split[1]))
        vetorInserirAB1y.append(int(split[2]))
    i+=1

i = 0
while i < tamanhoAB5 -1:
    split = yAB5[i].split(":")
    if(split[0] == 'I'):
        vetorInserirAB5x.append(int(split[1]))
        vetorInserirAB5y.append(int(split[2]))
    i+=1

i = 0
while i < tamanhoAB10 -1:
    split = yAB10[i].split(":")
    if(split[0] == 'I'):
        vetorInserirAB10x.append(int(split[1]))
        vetorInserirAB10y.append(int(split[2]))
    i+=1


# plot lines
# plt.subplot(1, 2, 1)
plt.figure(figsize=(9, 20))
plt.plot(vetorInserirAVLx, vetorInserirAVLy, label = 'Arvore AVL')
plt.plot(vetorInserirARNx, vetorInserirARNy, label = 'Arvore Rubro Negra')
plt.plot(vetorInserirAB1x, vetorInserirAB1y, label = 'Arvore B, ordem 1')
plt.plot(vetorInserirAB5x, vetorInserirAB5y, label = 'Arvore B, ordem 5')
plt.plot(vetorInserirAB10x, vetorInserirAB10y, label = 'Arvore B, ordem 10')



plt.xticks(range(0, 10500, 1000))
plt.yticks(range(0, 45, 5))
#INSERIR ARVORE B AQUI
plt.title("INSERÇÃO")

# plt.subplot(1, 2, 2)
# plt.plot(np.array(vetorRemoverARNx), np.array(vetorRemoverARNy), label = 'Arvore Rubro Negra')
# plt.plot(vetorRemoverAVLx, vetorRemoverAVLy, label = 'Arvore AVL')
# #INSERIR ARVORE B AQUI
# plt.title("REMOÇÃO")


plt.legend()
plt.show()

