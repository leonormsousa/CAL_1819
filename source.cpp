#include "Company.h"
#include "graphviewer.h"
#include <string>
#include <unistd.h>

using namespace std;

int main(){


void funcionalidades(Company &p)
{
	while (true)
	{
	  try
	  {
		int option;
		cout << endl << "Opcoes:" << endl;
		cout << "1 - Adicionar Autocarro " << endl;
		cout << "2 - Adicionar Turista " << endl;
		cout << "3 - Remover Autocarro " << endl;
		cout << "4 - Remover Turista " << endl;
		cout << "5 - Adicionar pontos de interesse a um turista " << endl;
		cout << "6 - Remover pontos de interesse de um turista " << endl;
		cout << "7 - Assinalar uma rua como estando em obras " << endl;
		cout << "8 - Assinalar as obras de uma determinada rua como terminadas  " << endl;
		cout << "9 - Calculo do caminho mais curto/rentavel sem grupos " << endl;
		cout << "10 - Calculo do caminho mais curto/rentavel com grupos sem limite " << endl;
		cout << "11 - Calculo do caminho mais curto/rentavel com grupos limitados " << endl;

		cout << "0 - Exit" << endl << endl;
		cout << "Opcao? ";
		cin >> option;
		option = toupper(option);
		while (!cin || ((option != 0) && (option != 1) && (option != 2) && (option != 3) && (option != 4) && (option != 5) && (option != 6) && (option != 7) && (option != 8) && (option !=9) && (option != 10) && (option != 11) && (option != 12) && (option != 13) && (option != 14) && (option != 15) && (option != 16) && (option != 17) && (option != 18) && (option != 19) && (option != 20)))
		{
			cin.clear();
			cin.ignore(100000, '\n');
			cout << endl << "Invalid Input" << endl;
			cout << "Option? ";
			cin >> option;
		}
		switch (option)
		{
		case 1: {
			string id;
		
			cout << "Introduza o ID representativo do autocarro: ";
			cin >> id;
			cout << endl;
			p.addBus(stoi(id));
			
		}
		case 2: {
            string nome, id;

			cout << "Nome do turista a ser adicionado: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, nome);
			cout << endl;

			cout << "Introduza o id do turista: ";
			cin >> id;
			cout << endl;
			p.addTourist(stoi(id), nome);
			break;
		}
		case 3: {
			string id;
			cout << "ID do autocarro a remover: ";
			cin >> id;
			cout << endl;
			p.removeBus(stoi(id));
			cout << "Autocarro " << id << " removido com sucesso." << endl;
			break;
		}
		case 4: {
			string id;
			cout << "ID do turista a remover: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, id);
			cout << endl;
			p.removeTourist(stoi(id));
			cout << "Turista " << id << " removido com sucesso." << endl;
			break;
		}
        case 5: {
            string id, poiID;
            cout << "ID do turista ao qual adicionar o ponto de interesse:";
            if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, id);            
            cout << endl;
            cout << "ID do ponto de interesse a adicionar: ";
            if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, poiID);            
            cout << endl;
            PoI poi = PoI(stoi(poiID),0,0);
            vector<Tourist>::iterator it = find(p.getTourists().begin(), p.getTourists().begin(), Tourist(stoi(id), ""));
           	vector<PoI>::iterator it2 = find(p.getPois().begin(), p.getPois().end(), poi);
            it->addPoI( &(*it2));
            break;
        }
        case 6:{
            string id, poiID;
            cout << "ID do turista do qual remover o ponto de interesse:";
            if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, id);            
            cout << endl;
            cout << "ID do ponto de interesse a remover: ";
            if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, poiID);            
            cout << endl;
            PoI poi = PoI(stoi(poiID),0,0);
            vector<Tourist>::iterator it = find(p.getTourists().begin(), p.getTourists().begin(), Tourist(stoi(id), ""));
           	vector<PoI>::iterator it2 = find(p.getPois().begin(), p.getPois().end(), poi);
            it->removePoI( &(*it2));
            break;
        }
        case 7: {
            break;
        }
        case 8:{
            break;
        }
        case 9: {
            break;
        }
        case 10:{
            break;
        }
        case 11: {
            break;
        }
		
		case 0:exit(0);
		}
	  }

	  	catch (exception &e)
	  	{
	  		e.what();
	  	}
	}
}

int main()
{
    	/*
    Company p = Company();
    string edgeFile= "T03/Aveiro/T03_Edges_Aveiro.txt";
    string vertexFile= "T03/Aveiro/T03_Nodes_X_Y_Aveiro.txt";
    string tagsFile= "T03/Aveiro/T03_tags_Aveiro.txt";

    p.initializeGraph(edgeFile, vertexFile, tagsFile);
    */

	GraphViewer * gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	Company p = Company();
	string edgeFile= "T03/Aveiro/T03_Edges_Aveiro.txt";
	string vertexFile= "T03/Aveiro/T03_Nodes_X_Y_Aveiro.txt";
	string tagsFile= "T03/Aveiro/T03_tags_Aveiro.txt";

	p.initializeGraph(edgeFile, vertexFile, tagsFile);

	// for(size_t i=0; i<p.getPois().size();i++)
	// {
	// 	gv->addNode(p.getPois()[i].getId());
	// 	//gv->rearrange();
	// }
	// // gv->addEdge(0, 0, 1, EdgeType::DIRECTED);

	// // gv->setVertexLabel(2, "This is a node");
	// // gv->setEdgeLabel(0, "This an edge");
	// // gv->setVertexColor(2, "green");
	// // gv->setEdgeColor(0, "yellow");
	// // gv->setBackground("image.png");
	// gv->rearrange();
	// sleep(5);
	// gv->closeWindow();
  
		cout << "==========================" << endl;
		cout << "===  CITY SIGHTSEEING  ===" << endl;
		cout << "==========================" << endl;

        Company p = Company();
        funcionalidades(p);
            
        cout << "=======================================================================================================" << endl << endl;
        cout << "Program developed by: " << endl;
        cout << "Joao Praca" << endl <<  "Leonor M. Sousa" << endl << "Silvia Rocha" << endl <<
                "Informatics and Computing Engineering Students in the Faculty of Engineering of the University of Porto"<< endl << endl;
        return 0;
                
		
	return 0;
}
