    
		int calcPosIns(int chave) {
        if (elem == 0) { //Se for zero j� inseri o elemento
            arv[elem] = hash(chave);
		}
		if (elem == TAM) { //Se for igual a tamanho m�ximo ele sai e n�o inseri
			cout << "N�o h� como inserir novos elementos" << endl <<
		}
		if ((arv[elem]) > 0) { // Se 0 vazio, se -1 vazio
			int aux = inc(chave);
			int auxx = Inc(arv[elem].getNo().chave); //Aqui quero pegar a chave do elemento que est� na posi��o que deveria inserir
				if ((arv[elem + aux] == 0) || (arv[elem + aux] == -1)) { //Aqui eu testo se a posi��o a esquerda esta vazia e se sim add a chave
					arv[elem + aux] = chave;
				}
				if ((arv[elem + auxx] == 0) || (arv[elem + auxx] == -1)) { //Aqui eu testo se a posi��o a direita esta vazia e se sim add a chave
						arv[elem + auxx] = arv[elem];
						arv[elem] = chave;
				} else { //Se chegar aqui chamo a mesma por recursividade para a esquerda e depois para a direita caso seja necess�rio
						if ((arv[elem + aux].getNoEsq())=! nill) {
							calcPosIns(arv[elem + aux].getNoEsq().chave); //A inten��o � passar a chave da esquerda
						} 
						if ((arv[elem + aux].getNoDir())=! nill) {
							calcPosIns(arv[elem + aux].getNoDir().chave); //A inten��o � passar a chave da direita
						}
							
				}
		}
			return 1; //Acho que seja desnecess�rio ou servir� de retorno tipo ok que achou...
    }

