#include "Company.h"
#include "graphviewer.h"
#include <string>
#include <unistd.h>

using namespace std;

void features(Company &p)
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
		while (!cin || ((option != 0) && (option != 1) && (option != 2) && (option != 3) && (option != 4) && (option != 5) && (option != 6) && (option != 7) && (option != 8) && (option !=9) && (option != 10) && (option != 11) ))
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
			break;
		}
		case 2: {
            string nome, id;

			cout << "Nome do turista a ser adicionado: ";
			if (cin.peek() != EOF)
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
			if (cin.peek() != EOF)
				cin.ignore(100000, '\n');
			getline(cin, id);
			cout << endl;
			if(p.removeTourist(stoi(id)))
				cout << "Turista " << id << " removido com sucesso." << endl;
			else
				cout << "Turista " << id << " nao encontrado." << endl;
			break;
		}
        case 5: {
            string id, poiID;
            cout << "ID do turista ao qual adicionar o ponto de interesse:";
            if (cin.peek() != EOF)
				cin.ignore(100000, '\n');
			getline(cin, id);            
            cout << endl;
            cout << "ID do ponto de interesse a adicionar: ";
//            if (cin.peek() != EOF)
//				cin.ignore(100000, '\n');
			getline(cin, poiID);            
            cout << endl;
            cout<<"Aqui"<< endl;
            vector<Tourist>::iterator it=find(p.getTourists().begin(), p.getTourists().end(), Tourist(stoi(id), ""));
            cout<<"Aqui"<< endl;

            if(it!=p.getTourists().end()){
            	it->addPoI(p.findPoI(stoi(poiID)));
            	cout << "Ponto de interesse adicionado ao turista " << it->getName() <<endl;
            	cout << it->getPoIs()[0]->getX()<<endl;
            }
            else
            	cout<< "O id indicado não corresponde a nenhum turista"<<endl;
            break;
        }
        case 6:{
            string id, poiID;
            cout << "ID do turista do qual remover o ponto de interesse:";
            if (cin.peek() != EOF)
				cin.ignore(100000, '\n');
			getline(cin, id);            
            cout << endl;
            cout << "ID do ponto de interesse a remover: ";
            if (cin.peek() != EOF)
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
        	string id, id1;
        	cout << "ID do ponto de interesse de origem da estrada: ";
        	if (cin.peek() != EOF)
				cin.ignore(100000, '\n');
			getline(cin, id);
			cout << endl;
			cout << "ID do ponto de interesse de origem da estrada: ";
//			if (cin.peek() != EOF)
//				cin.ignore(100000, '\n');
			getline(cin, id1);
			cout << endl;

			double distance = sqrt(pow(p.findPoI(stoi(id1))->getX() - p.findPoI(stoi(id))->getX(), 2) + pow(p.findPoI(stoi(id1))->getY() - p.findPoI(stoi(id))->getY(), 2));
			double f=0;

			Edge<PoI*> edge= Edge<PoI*>(p.findVertex(stoi(id)), p.findVertex(stoi(id1)), distance,f);
			p.addUnavailableRoad(edge);
			cout << p.getUnavailableRoads()[0].getWeight()<<endl;
            break;
        }
        case 8:{
        	string id, id1;
			cout << "ID do ponto de interesse de origem da estrada: ";
			if (cin.peek() != EOF)
				cin.ignore(100000, '\n');
			getline(cin, id);
			cout << endl;
			cout << "ID do ponto de interesse de origem da estrada: ";
//			if (cin.peek() != EOF)
//				cin.ignore(100000, '\n');
			getline(cin, id1);
			cout << endl;
			double distance = sqrt(pow(p.findPoI(stoi(id1))->getX() - p.findPoI(stoi(id))->getX(), 2) + pow(p.findPoI(stoi(id1))->getY() - p.findPoI(stoi(id))->getY(), 2));
			double f=0;
			Edge<PoI*> edge= Edge<PoI*>(p.findVertex(stoi(id)), p.findVertex(stoi(id1)), distance,f);
			p.removeUnavailableRoad(edge);
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
		
		case 0:{
			return;
			break;
		}

		}
	  }

	  	catch (exception &e)
	  	{
	  		e.what();
	  	}
	}
}

string getMapName()
{
	while (true)
		{
		  try
		  {
			int option;

			cout << endl << "Escolha um mapa (numero):" << endl;
			cout << "1 - Aveiro " << endl;
			cout << "2 - Braga " << endl;
			cout << "3 - Coimbra " << endl;
			cout << "4 - Ermesinde " << endl;
			cout << "5 - Fafe " << endl;
			cout << "6 - Gondomar " << endl;
			cout << "7 - Lisboa " << endl;
			cout << "8 - Maia  " << endl;
			cout << "9 - Porto " << endl;
			cout << "10 - Portugal " << endl;
			cout << "11 - Viseu " << endl;

			//cout << "0 - Exit" << endl << endl;
			cout << endl << "Opcao? ";
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
				return "Aveiro";
				break;
			}
			case 2: {
	            return "Braga";
				break;
			}
			case 3: {
				return "Coimbra";
				break;
			}
			case 4: {
				return "Ermesinde";
				break;
			}
	        case 5: {
	            return "Fafe";
	            break;
	        }
	        case 6:{
	            return "Gondomar";
	            break;
	        }
	        case 7: {
	        	return "Lisboa";
	            break;
	        }
	        case 8:{
	        	return "Maia";
	            break;
	        }
	        case 9: {
	        	return "Porto";
	            break;
	        }
	        case 10:{
	        	return "Portugal";
	            break;
	        }
	        case 11: {
	        	return "Viseu";
	            break;
	        }

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
	cout << "==========================" << endl;
	cout << "===  CITY SIGHTSEEING  ===" << endl;
	cout << "==========================" << endl;

	string city = getMapName();

	/*GraphViewer * gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");*/

	Company p = Company();
	string edgeFile= "T03/" + city + "/T03_Edges_" + city + ".txt";
	string vertexFile= "T03/" + city + "/T03_Nodes_X_Y_" + city + ".txt";
	string tagsFile= "T03/" + city + "/T03_tags_" + city + ".txt";

	cout << endl << edgeFile << endl << endl;

	p.initializeGraph(edgeFile, vertexFile, tagsFile);

	/*for(size_t i=0; i<p.getPois().size();i++)
	{
		gv->addNode(p.getPois()[i].getId());
	}*/
	/*
	gv->addEdge(0, 0, 1, EdgeType::DIRECTED);

	gv->setVertexLabel(2, "This is a node");
	gv->setEdgeLabel(0, "This an edge");
	gv->setVertexColor(2, "green");
	gv->setEdgeColor(0, "yellow");
	gv->setBackground("image.png");
	*/
	//gv->rearrange();
	//sleep(5);
	//gv->closeWindow();

	features(p);

	cout << endl << "=======================================================================================================" << endl << endl;
	cout << "Program developed by: " << endl;
	cout << "Joao Praca" << endl <<  "Leonor M. Sousa" << endl << "Silvia Rocha" << endl <<
			"Informatics and Computing Engineering Students in the Faculty of Engineering of the University of Porto"<< endl << endl;

		
	return 0;
}
