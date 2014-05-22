    
		int calcPosIns(int chave) {
        if (elem == 0) { //Se for zero já inseri o elemento
            arv[elem] = hash(chave);
		}
		if (elem == TAM) { //Se for igual a tamanho máximo ele sai e não inseri
			cout << "Não há como inserir novos elementos" << endl <<
		}
		if ((arv[elem]) > 0) { // Se 0 vazio, se -1 vazio
			int aux = inc(chave);
			int auxx = Inc(arv[elem].getNo().chave); //Aqui quero pegar a chave do elemento que está na posição que deveria inserir
				if ((arv[elem + aux] == 0) || (arv[elem + aux] == -1)) { //Aqui eu testo se a posição a esquerda esta vazia e se sim add a chave
					arv[elem + aux] = chave;
				}
				if ((arv[elem + auxx] == 0) || (arv[elem + auxx] == -1)) { //Aqui eu testo se a posição a direita esta vazia e se sim add a chave
						arv[elem + auxx] = arv[elem];
						arv[elem] = chave;
				} else { //Se chegar aqui chamo a mesma por recursividade para a esquerda e depois para a direita caso seja necessário
						if ((arv[elem + aux].getNoEsq())=! nill) {
							calcPosIns(arv[elem + aux].getNoEsq().chave); //A intenção é passar a chave da esquerda
						} 
						if ((arv[elem + aux].getNoDir())=! nill) {
							calcPosIns(arv[elem + aux].getNoDir().chave); //A intenção é passar a chave da direita
						}
							
				}
		}
			return 1; //Acho que seja desnecessário ou servirá de retorno tipo ok que achou...
    }

