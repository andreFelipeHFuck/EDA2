import matplotlib.pyplot as plt
import numpy as np
  
# create data
arquivoARN = open("arvoreRubroNegra.txt", "r")
arquivoAVL = open("arvoreAVL.txt", "r")
dadosARN = arquivoARN.read()
dadosAVL = arquivoAVL.read()

yARN = dadosARN.split(";")
yAVL = dadosAVL.split(";")
print(yAVL)

tamanhoARN = len(yARN)
tamanhoAVL = len(yAVL)
i = 0
vetorInserirARNx = []
vetorInserirARNy = []
vetorRemoverARNx = []
vetorRemoverARNy = []

vetorInserirAVLx = []
vetorInserirAVLy = []
vetorRemoverAVLx = []
vetorRemoverAVLy = []

while i < tamanhoARN -1:
    split = yARN[i].split(":")
    if(split[0] == 'I'):
        vetorInserirARNx.append(split[1])
        vetorInserirARNy.append(split[2])
    else:
        vetorRemoverARNx.append(split[1])
        vetorRemoverARNy.append(split[2])
    i+=1

i = 0
while i < tamanhoAVL -1:
    split = yAVL[i].split(":")
    if(split[0] == 'I'):
        vetorInserirAVLx.append(split[1])
        vetorInserirAVLy.append(split[2])
    else:
        vetorRemoverAVLx.append(split[1])
        vetorRemoverAVLy.append(split[2])
    i+=1



# plot lines
plt.subplot(1, 2, 1)
plt.plot(np.array(vetorInserirARNx), np.array(vetorInserirARNy), label = 'Arvore Rubro Negra')
plt.plot(vetorInserirAVLx, vetorInserirAVLy, label = 'Arvore AVL')
#INSERIR ARVORE B AQUI
plt.title("INSERÇÃO")

plt.subplot(1, 2, 2)
plt.plot(np.array(vetorRemoverARNx), np.array(vetorRemoverARNy), label = 'Arvore Rubro Negra')
plt.plot(vetorRemoverAVLx, vetorRemoverAVLy, label = 'Arvore AVL')
#INSERIR ARVORE B AQUI
plt.title("REMOÇÃO")


plt.legend()
plt.show()