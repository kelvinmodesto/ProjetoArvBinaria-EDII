	#include <iostream>
	#include <fstream>
	#include <string>
	#include <stdlib.h>
	
	#define TAMANHO 11
	#define NOME_ARQUIVO "dados_modelo.dat"
	
	using namespace std;

	struct no {
			int id;
			char termo[50];
			char sig[50];
	};

	void menu();	
	void cadastrar_termo();
	void exibirTermo();
	void gera_arquivo_modelo();
	void buscarTermo();
	void gera_arquivo_vazio();
	void remover();

	int main () {
		system("cls");
		int i, opcao;
		menu();
		do {
			cout << "|Entre com uma opcao: ";
			cin >> opcao;;
			cout << endl;

			switch (opcao) {
				case 0:
					system("cls");
					menu();
					gera_arquivo_modelo();					
				break;
				case 1:
					system("cls");
					menu();
					gera_arquivo_vazio();
					break;
				case 2:
					system("cls");
					menu();
					cadastrar_termo();
					break;							
				case 3:					
					system("cls");
					menu();
					remover();
					break;
				case 4:
					system("cls");
					menu();
					buscarTermo();
				break;
				case 5:
					system("cls");
					menu();
					exibirTermo();
					break;				
				case 6:
					break;
				default:
					system("cls");
					menu();
					cout << "Opcao invalida! Utilize menu.\n";
			}
		} while (opcao != 6);
		
		cout << "S A I N D O . . . " << endl;
		
		return 0;
	}
	//*********************************************************************************
	
	void menu() {
		cout << "|===============================================|\n";
		cout << "|\t\tSISTEMA GLOSSARIO v0.01 \t|\n";
		cout << "|===============================================|\n";
		cout << "|0 - Criar arquivo de modelo \t\t\t|\n";
		cout << "|1 - Gera arquivo vazio \t\t\t|\n";
		cout << "|2 - Inserir termo \t\t\t\t|\n";
		cout << "|3 - Remover termo \t\t\t\t|\n";
		cout << "|4 - Buscar termo no arquivo\t\t\t|\n";
		cout << "|5 - Exibir todos os termos\t\t\t|\n";
		cout << "|6 - Sair\t\t\t\t\t|\n";
		cout << "|-----------------------------------------------|\n";
	}
	//*********************************************************************************
	
	void cadastrar_termo(){
		no no;
		fstream arquivo(NOME_ARQUIVO, ios::in| ios::out | ios::binary );
		if (!arquivo)
		{
			cerr << "Arquivo não pode ser aberto.";
			exit(1);
		}

		cout << "|ID: ";
		cin.get();
		cin >> no.id;
    
		cout << "|Termo: ";
		cin.get();
		cin.getline(no.termo, 50);
    
		cout << "|Significado: ";
		cin.getline(no.sig, 50);

		arquivo.seekp(( no.id % TAMANHO ) * sizeof(no));				
		arquivo.write( reinterpret_cast<const char*>(&no), sizeof(no) );	
		arquivo.close();
		
		cout << "|Termo \'" << no.termo << "\' inserido na posicao " << (no.id % TAMANHO ) << " \t\t\t\t" << endl;
		cout << "|-----------------------------------------------|" << endl;
	}
	//*********************************************************************************
	
	void remover(){
		int chave;
		fstream arquivo(NOME_ARQUIVO, ios::in| ios::out | ios::binary );
		
		cout << "|ID a remover: ";
		cin.get();
		cin >> chave;
		
		arquivo.seekp((chave % 11) * sizeof(no)); 	// ainda não detecta colisao, até pq quem vai fazer isso vai ser a arvore
													// não precisa alteração.
		no no = {-1, "", ""};
		
		arquivo.write( reinterpret_cast<const char*>(&no), sizeof(no) );
		cout << "|Termo \'" << chave << "\' removido com sucesso!\t\t\t\t" << endl;
		cout << "|-----------------------------------------------|" << endl;		
	}
	
	void exibirTermo() {
		no no;
		ifstream leitura;
		leitura.open(NOME_ARQUIVO, ios::binary ); // abre arquivo para leitura
		
		if (!leitura) { // verifica se o arquivo existe/nome correto
			cerr << "Arquivo nao pode ser aberto para leitura!" << endl;
			return;
		}
		
		cout << "|ID\t" << "|TERMO\t\t" << "|SIGNIFICADO\t\t|" << endl;
		cout << "|-----------------------------------------------|" << endl;
		leitura.seekg(0);
		leitura.read((char*)&no, sizeof(no));
		while ((leitura) && (!leitura.eof())) { // varre o arquvo binario e armazena cada no(struct) na variavel no e exibe na tela ate encontrar eof
			cout << "|" << no.id << "\t" << no.termo << "\t\t" << no.sig << "\t\t" << endl;
			leitura.read((char*)&no, sizeof(no));
		}
		cout << "|-----------------------------------------------\n";
		leitura.close(); // fecha arquivo
	}
	//*********************************************************************************
	
	void buscarTermo(){
	
		int chave;
		cin >> chave;
		
		//na minha implementaçao, eu simplesmente faço o calculo com mod 11
		// no trabalho final, é aqui que o metodo de busca na arvore binaria
		// vai acontecer... ele vai procurar a posicao onde a chave se encontra
		//e vai me informar pra que eu possa dizer onde posicionar o ponteiro
		// vai ficar assim:
		// int posicao = buscaPosicao( chave ); // esse metodo usa a arvore binaria pra achar o dado
		
		int posicao = (chave % 11) * sizeof(no);// por enquanto vai ficar assim
	
		no no;
		ifstream leitura;
		leitura.open( NOME_ARQUIVO, ios::binary ); // abre arquivo para leitura
		
		if (!leitura) { // verifica se o arquivo existe/nome correto
			cerr << "Arquivo nao pode ser aberto para leitura!" << endl;
			return;
		}
		
		cout << "|ID\t" << "|TERMO\t\t" << "|SIGNIFICADO\t\t|" << endl;
		cout << "|-----------------------------------------------|" << endl;
		leitura.seekg(posicao);//posiciono o ponteiro no registro que desejo
		leitura.read((char*)&no, sizeof(no));
		
		cout << "|" << no.id << "\t" << no.termo << "\t\t" << no.sig << "\t\t" << endl;
		leitura.read((char*)&no, sizeof(no));
		
		cout << "|-----------------------------------------------\n";
		leitura.close(); // fecha arquivo	
	}
	//*********************************************************************************
	
	void gera_arquivo_modelo(){
		// esse arquivo será o modelo para pesquisa e alterações
		// os nos estão na ordem e posicao que se encontram nos
		// slides que o prof usou em sala de aula
		no no0 = {41, "Mancebo", "Moco, velador, cabide para  roupa"};
		no no1 = {39, "Politipo", "Que tem muitos tipos"};
		no no2 = {13, "Conego", "Dignidade eclesiastica"};
		no no3 = {0, "", ""};
		no no4 = {0, "", ""};
		no no5 = {27, "Glandado", "Que termina em glande"};
		no no6 = {16, "Redil", "Curral, aprisco, gremio, paroquia"};
		no no7 = {18, "Tosta", "Torrada, Bolo em forma de torrada"};
		no no8 = {17, "Urural", "Especie de jacare de papo amarelo"};
		no no9 = {19, "Esquiça", "Batoque do buraco nas vasilhas de vinho"};
		no no10 = {28, "Napeias", "Ninfa dos bosques e dos prados."};
		
		ofstream arquivo; // define objeto para escrita no arquivo
		arquivo.open( NOME_ARQUIVO, ios::out | ios::binary ); // abre arquivo para escrita
		
		if (!arquivo) { // verifica se nao ha erro na abertura do arquivo
			cerr << "Arquivo nao pode ser aberto para gravacao!" << endl;
			exit(1);
		}
		
		arquivo.write((char*)&no0, sizeof(no) );
		arquivo.write((char*)&no1, sizeof(no) );
		arquivo.write((char*)&no2, sizeof(no) );
		arquivo.write((char*)&no3, sizeof(no) );
		arquivo.write((char*)&no4, sizeof(no) );
		arquivo.write((char*)&no5, sizeof(no) );
		arquivo.write((char*)&no6, sizeof(no) );
		arquivo.write((char*)&no7, sizeof(no) );
		arquivo.write((char*)&no8, sizeof(no) );
		arquivo.write((char*)&no9, sizeof(no) );
		arquivo.write((char*)&no10, sizeof(no) );		
		
		cout << "|Arquivo modelo usado para o trabalho criado!\t|" << endl;
		cout << "|-----------------------------------------------|" << endl;
		arquivo.close();			
	}
	//*********************************************************************************
	
	void gera_arquivo_vazio(){
	
		ofstream arquivo;
		arquivo.open( NOME_ARQUIVO, ios::binary );		
		no no = {0,"",""};
		
		for( int i = 0; i < TAMANHO; i++)
			arquivo.write((char*)&no,(sizeof(struct no)));
			
		cout << "|Arquivo vazio usado para o trabalho criado!\t|" << endl;
		cout << "|-----------------------------------------------|" << endl;			
			
	}
	