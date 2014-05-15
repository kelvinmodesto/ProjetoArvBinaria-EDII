	#include <iostream>
	#include <fstream>
	#include <string>
	#include <stdlib.h>
	using namespace std;

	class registro {
	public:
		int id;
		char termo[50];
		char sig[50];
	};

	void menu();
	void inicializarArquivoDados();
	void cadastrarTermo();
	void alterarTermo();
	void excluirTermo();
	void exibirTermo();

	int main () {
		int i, opcao;
		menu();
		do {
			cout << "Entre com uma opcao: ";
			cin >> opcao;;
			cout << endl;

			switch (opcao) {
				case 0:
					system("cls");
					menu();
					inicializarArquivoDados();
				break;
				case 1:
					system("cls");
					menu();
					cadastrarTermo();
				break;
				case 2:
					system("cls");
					alterarTermo();
					break;
				case 3:
					system("cls");
					menu();
					excluirTermo();
					break;
				case 4:
					system("cls");
					menu();
					exibirTermo();
					break;
				case 5:
					cout << "S A I N D O ...\n";
					break;
				default:
					system("cls");
					menu();
					cout << "Opcao invalida! Utilize menu.\n";
			}
		} while (opcao != 5);
		return 0;
	}
	//*********************************************************************************
	void menu() {
		cout << "|===============================================|\n";
		cout << "|\t\tSISTEMA GLOSSARIO v1.0\t\t|\n";
		cout << "|===============================================|\n";
		cout << "|0 - Criar arquivo de dados vazio\t\t|\n";
		cout << "|1 - Cadastrar termo/significado\t\t|\n";
		cout << "|2 - Alterar termo/significado\t\t\t|\n";
		cout << "|3 - Excluir termo/significado\t\t\t|\n";
		cout << "|4 - Consultar termo/significado\t\t|\n";
		cout << "|5 - Sair\t\t\t\t\t|\n";
		cout << "|-----------------------------------------------|\n";
	}
	//*********************************************************************************
	void inicializarArquivoDados() { // cria arquivo, inicializando 100 registros vazios
		registro inicializarVazio = {0,"",""}; // variavel auxiliar
		ofstream arquivo; // define objeto para escrita no arquivo
		arquivo.open("dadosGlossario.dat", ios::out | ios::binary ); // abre arquivo para escrita
		
		if (!arquivo) { // verifica se nao ha erro na abertura do arquivo
			cerr << "Arquivo nao pode ser aberto para gravacao!" << endl;
			exit(1);
		}
		
		for (int i=0; i<11; i++) { // grava no arquivo 100 registros vazio para realizar controle dos mesmos
			arquivo.write((char*)&inicializarVazio, sizeof(registro) );
		}
		arquivo.close();
	}
	//*********************************************************************************
	void cadastrarTermo() {
		registro reg;
		ofstream arquivo;
		arquivo.open("dadosGlossario.dat", ios::out | ios::app | ios::binary  ); // definindo objeto para gravacao arquivo
		
		if (!arquivo) { // verifica se o arquivo existe/nome incorreto
			cerr << "Arquivo nao pode ser aberto para gravacao!" << endl;
			return;
		}

		cout << "|ID: ";
		cin.get();
		cin >> reg.id;
		
		cout << "|Termo: ";
		cin.get();
		cin.getline(reg.termo, 50);
		
		cout << "|Significado: ";
		cin.getline(reg.sig, 50);
		
		arquivo.clear();
		arquivo.seekp((reg.id % 11) * sizeof(registro));
		arquivo.write((char*)&reg,(sizeof(registro)));
		
		cout << "|-----------------------------------------------\n";
		arquivo.close();
	}
	//*********************************************************************************
	void alterarTermo() {
		cout << "alterar termo/sig\n";
	}
	//*********************************************************************************
	void excluirTermo() {

	}
	//*********************************************************************************
	void exibirTermo() {
		registro reg;
		ifstream leitura;
		leitura.open("dadosGlossario.dat", ios::binary ); // abre arquivo para leitura
		
		if (!leitura) { // verifica se o arquivo existe/nome correto
			cerr << "Arquivo nao pode ser aberto para leitura!" << endl;
			return;
		}
		
		cout << "|ID\t" << "|TERMO\t\t" << "|SIGNIFICADO\t\t|" << endl;
		cout << "|-----------------------------------------------|" << endl;
		leitura.seekg(0);
		leitura.read((char*)&reg, sizeof(registro));
		while ((leitura) && (!leitura.eof())) { // varre o arquvo binario e armazena cada registro(struct) na variavel reg e exibe na tela ate encontrar eof
			cout << "|" << reg.id << "\t" << reg.termo << "\t\t" << reg.sig << "\t\t" << endl;
			leitura.read((char*)&reg, sizeof(registro));
		}
		cout << "|-----------------------------------------------\n";
		leitura.close(); // fecha arquivo
	}
	//*********************************************************************************