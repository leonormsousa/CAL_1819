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
		cout << "10 - Calculo do caminho mais curto/rentavel com grupos limitados " << endl;
		cout << "11 - Calculo do caminho mais curto/rentavel sem grupos usando algoritmo ganancioso " << endl;
		cout << "0 - Exit" << endl << endl;
		cout << "Opcao? ";
		cin >> option;
		option = toupper(option);
		while (!cin || ((option != 0) && (option != 1) && (option != 2) && (option != 3) && (option != 4) && (option != 5) && (option != 6) && (option != 7) && (option != 8) && (option !=9) && (option != 10) && (option != 11)))
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

			if(p.addBus(stoi(id)))
				cout << "O autocarro " << id << " foi adicionado com sucesso." << endl;
			else
				cout << "O autocarro " << id << " ja existe." << endl;
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
			if(p.addTourist(stoi(id), nome))
				cout << "O turista " << nome << " foi adicionado com sucesso." << endl;
			else
				cout << "O turista com o id " << id << " ja existe." << endl;
			break;
		}
		case 3: {
			string id;
			cout << "ID do autocarro a remover: ";
			cin >> id;
			cout << endl;
			if(p.removeBus(stoi(id)))
				cout << "Autocarro " << id << " removido com sucesso." << endl;
			else
				cout << "Autocarro " << id << " nao encontrado." << endl;
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
            cout << "ID do turista ao qual adicionar o ponto de interesse: ";
            if (cin.peek() != EOF)
				cin.ignore(100000, '\n');
			getline(cin, id);            
            cout << endl;
            cout << "ID do ponto de interesse a adicionar: ";
//            if (cin.peek() != EOF)
//				cin.ignore(100000, '\n');
			getline(cin, poiID);            
            cout << endl;
            vector<Tourist>::iterator it=find(p.getTourists()->begin(), p.getTourists()->end(), Tourist(stoi(id), ""));
            if(it!=p.getTourists()->end()){
            	PoI* poi;
            	poi = p.findPoI(stoi(poiID));
            	if(poi != NULL){
					if(it->addPoI(poi))
						cout << "Ponto de interesse com id " << poiID << " adicionado ao turista " << it->getName() <<endl;
					else
						cout << "Ponto de interesse com id " << poiID << " ja foi previamente adicionado ao turista " << it->getName() <<endl;
            	}
            	else
            		cout << "Ponto de interesse com id " << poiID << " nao existe." << endl;
            }
            else
            	cout<< "O id " << id << " nao corresponde a nenhum turista"<<endl;
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
           // if (cin.peek() != EOF)
				//cin.ignore(100000, '\n');
			getline(cin, poiID);
            cout << endl;
            PoI poi = PoI(stoi(poiID),0,0);
            vector<Tourist>::iterator it = find(p.getTourists()->begin(), p.getTourists()->begin(), Tourist(stoi(id), ""));
           	if(it!=p.getTourists()->end()){
				if(it->removePoI(p.findPoI(stoi(poiID))))
					cout << "Ponto de interesse removido do turista " << it->getName() <<endl;
				else
					cout << "O turista nao tem nenhum POI com o ID " << stoi(poiID) <<endl;
			}
			else
				cout<< "O id indicado nao corresponde a nenhum turista"<<endl;
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

			Vertex<PoI*>* p1 = p.findVertex(stoi(id));
			if(p1==nullptr){
				cout << "Vertice de origem nao encontrado. " << endl;
				break;
			}
			Vertex<PoI*>* p2 = p.findVertex(stoi(id1));
			if(p2==nullptr){
				cout << "Vertice de destino nao encontrado" << endl;
				break;
			}

			Edge<PoI*> edge= Edge<PoI*>(p1, p2 , distance,f);
			cout << edge.getWeight() << endl;
			p.addUnavailableRoad(edge);
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
        	string initial, final;
			cout << "Ponto de interesse inicial: ";
			cin>>initial;
			cout << "Ponto de interesse final: ";
			cin>>final;
			PoI* initialPoI = p.findPoI(stoi(initial));
			PoI* finalPoI = p.findPoI(stoi(final));

        	vector<PoI*> points;
        	for (size_t i=0; i<(*p.getTourists()).size(); i++)
        		points.insert(points.end(), (*(*(p.getTourists()))[i].getPoIs()).begin(), (*(*p.getTourists())[i].getPoIs()).end());

        	points.insert(points.begin(), initialPoI);
        	points.insert(points.end(), finalPoI);

        	sort(points.begin()+1, points.end()-1);
        	points.erase( unique(points.begin(), points.end()), points.end());

        	vector<PoI*>  routes = p.calculateRouteWithUnorderedPoints(points);
        	if(routes.size()==0)
        	{
        		cout << "Nao existe um caminho possivel para passar em todos os pontos selecionados" << endl;
        		break;
        	}

        	GraphViewer * gv = new GraphViewer(600, 600, false);
			gv->createWindow(600, 600);
			gv->defineVertexColor("blue");
			gv->defineEdgeColor("black");

			for (size_t j=0; j<routes.size()-1; j++)
			{
				cout << routes[j]->getId() << " -> ";
				gv->addNode(routes[j]->getId(), routes[j]->getX(), routes[j]->getY());
				gv->addEdge(routes[j]->getId(), routes[j]->getId(),routes[j+1]->getId(), 0);

			}
			cout << routes[routes.size()-1]->getId() << endl;
			gv->addNode(routes[routes.size()-1]->getId(), routes[routes.size()-1]->getX(),routes[routes.size()-1]->getY());
			gv->rearrange();
			sleep(7);
			gv->closeWindow();
			break;
        }
        case 10:{
        	string initial, final;
        	cout << "Ponto de interesse inicial: ";
        	cin>>initial;
        	cout << "Ponto de interesse final: ";
        	cin>>final;
        	PoI* initialPoI = p.findPoI(stoi(initial));
        	PoI* finalPoI = p.findPoI(stoi(final));

        	vector< vector<PoI*> > routes =  p.createGroupsBasedOnBuses(6, initialPoI, finalPoI);
           	GraphViewer * gv = new GraphViewer(600, 600, false);
			gv->createWindow(600, 600);
			gv->defineVertexColor("blue");
			gv->defineEdgeColor("black");
        	for (size_t i=0; i<routes.size(); i++)
			{
        		if(routes[i].size()==0)
        		{
        			cout << "Nao foi possivel encontrar um percurso a passar pelos pontos inicial e final indicados para alguns dos turistas"<< endl;
        			continue;
        		}
				for (size_t j=0; j<routes[i].size()-1; j++)
				{
					cout << routes[i][j]->getId() << " -> ";
					gv->addNode(routes[i][j]->getId(), routes[i][j]->getX(), routes[i][j]->getY());
					gv->addEdge(routes[i][j]->getId(), routes[i][j]->getId(),routes[i][j+1]->getId(), 0);
				}
				cout << routes[i][routes[i].size()-1]->getId() << endl;
				gv->addNode(routes[i][routes.size()-1]->getId(),routes[i][routes.size()-1]->getX(),routes[i][routes.size()-1]->getY());
				gv->rearrange();
				sleep(7);
				gv->closeWindow();
			}
            break;
        }
		case 11: {
        	string initial, final;
			cout << "Ponto de interesse inicial: ";
			cin>>initial;
			cout << "Ponto de interesse final: ";
			cin>>final;
			PoI* initialPoI = p.findPoI(stoi(initial));
			PoI* finalPoI = p.findPoI(stoi(final));
        	vector<PoI*> points;
        	for (size_t i=0; i<(*p.getTourists()).size(); i++)
        		points.insert(points.end(), (*(*(p.getTourists()))[i].getPoIs()).begin(), (*(*p.getTourists())[i].getPoIs()).end());

        	points.insert(points.begin(), initialPoI);
        	points.insert(points.end(), finalPoI);
        	sort(points.begin()+1, points.end()-1);
        	points.erase( unique(points.begin(), points.end()), points.end());

        	vector<PoI*>  routes = p.calculateRouteWithUnorderedPointsDynamic(points);
        	if(routes.size()==0)
        	{
        		cout << "Nao existe um caminho possivel para passar em todos os pontos selecionados" << endl;
        		break;
        	}

        	GraphViewer * gv = new GraphViewer(600, 600, false);
			gv->createWindow(600, 600);
			gv->defineVertexColor("blue");
			gv->defineEdgeColor("black");

			for (size_t j=0; j<routes.size()-1; j++)
			{
				cout << routes[j]->getId() << " -> ";
				gv->addNode(routes[j]->getId(), routes[j]->getX(), routes[j]->getY());
				gv->addEdge(routes[j]->getId(), routes[j]->getId(),routes[j+1]->getId(), 0);

			}
			cout << routes[routes.size()-1]->getId() << endl;
			gv->addNode(routes[routes.size()-1]->getId(), routes[routes.size()-1]->getX(), routes[routes.size()-1]->getY());
			gv->rearrange();
			sleep(7);
			gv->closeWindow();
			break;
        }
		case 0:{
			return;
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
			cout << "12 - Teste " << endl;

			//cout << "0 - Exit" << endl << endl;
			cout << endl << "Opcao? ";
			cin >> option;
			option = toupper(option);
			while (!cin || ((option != 0) && (option != 1) && (option != 2) && (option != 3) && (option != 4) && (option != 5) && (option != 6) && (option != 7) && (option != 8) && (option !=9) && (option != 10) && (option != 11) && (option != 12)))
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
	        case 12: {
				return "Teste";
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
/*
	GraphViewer * gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
*/
	Company p = Company();

	string edgeFile= "T03/" + city + "/T03_Edges_" + city + ".txt";
	string vertexFile= "T03/" + city + "/T03_Nodes_X_Y_" + city + ".txt";
	string tagsFile= "T03/" + city + "/T03_tags_" + city + ".txt";

	p.initializeGraph(edgeFile, vertexFile, tagsFile);

	vector<PoI*> pois;
	vector<PoI*> poiss;
	vector<PoI*> poisss;
	vector<PoI*> poissss;

	//pois.push_back(p.findPoI(994136199));
	pois.push_back(p.findPoI(994138487));
	pois.push_back(p.findPoI(994137873));
	pois.push_back(p.findPoI(994136619));
	poiss.push_back(p.findPoI(994135665));
	poiss.push_back(p.findPoI(994138090));
	//poiss.push_back(p.findPoI(994137583));
	poisss.push_back(p.findPoI(994137873));
	poisss.push_back(p.findPoI(994136619));
	poisss.push_back(p.findPoI(994135665));

	poissss.push_back(p.findPoI(26018641));
	poissss.push_back(p.findPoI(26018644));
	poissss.push_back(p.findPoI(26018646));
	poissss.push_back(p.findPoI(26018648));

	Tourist t(1, "dsadsdas", pois);
	Tourist t2(2, "dsadsdas", poiss);
	Tourist t3(3, "dsha", poisss);
	Tourist t4(4, "fjdsho", poissss);
	p.addTourist(t);
	p.addTourist(t2);
	p.addTourist(t3);
	//p.addTourist(t4);

	p.addBus(300);
	p.addBus(304);
	p.addBus(303);
	p.addBus(350);

	features(p);

	cout << endl << "=======================================================================================================" << endl << endl;
	cout << "Program developed by: " << endl;
	cout << "Joao Praca" << endl <<  "Leonor M. Sousa" << endl << "Silvia Rocha" << endl <<
			"Informatics and Computing Engineering Students in the Faculty of Engineering of the University of Porto"<< endl << endl;

	return 0;
}
