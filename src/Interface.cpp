#include "Interface.h"

Interface::Interface() {
	roadnetwork = new RoadNetwork();
	roadnetwork->readOSM();
}

Interface::~Interface() {}

void Interface::convertToGV() {
	roadnetwork->convertToGV();
}

void Interface::roadsBlocked(){
    cout << "------------------------------" << endl;
    cout << "ALTERACAO DO ESTADO DE UMA VIA" << endl;
    cout << "------------------------------" << endl;
    cout << endl;
    set<string> nomes_estradas = roadnetwork->getGraph().getEdgesNames();
    set<string> nome_estradas_organizadas;
    set<string> subset_nome_estardas;

    set<string>::iterator it = nomes_estradas.begin();
    while(it != nomes_estradas.end()){
    	string nome = *it;
    	nome_estradas_organizadas.insert(nome.substr(0, nome.find(' ')));
    	it++;
    }

    int m = 0;
	set<string>::iterator itn = nome_estradas_organizadas.begin();
	while (itn != nome_estradas_organizadas.end()) {
		m++;
		cout << m << ". ";
		cout << *itn;
		cout << endl;
		itn++;
	}

    int opcao1 = -1;
    cout << endl;
    cout << "Indique o numero da estrada: ";
	while (!(cin >> opcao1) || opcao1 < 1 || opcao1 > m) {
		cout << "Opcao invalida! Escolha uma nova opcao: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	cin.clear();
	cin.ignore(1000, '\n');

    cout << endl;

    itn = nome_estradas_organizadas.begin();
    advance(itn, (opcao1 - 1));
    string opcao_string = (*itn);

    m = 0;
    int p = 0;
    vector<int> indices;
    it = nomes_estradas.begin();
    while(it != nomes_estradas.end()){
    	string n = (*it);
    	m++;
    	if(n.substr(0, n.find(' ')) == opcao_string){
    		p++;
    		cout << p << ". ";
    		indices.push_back(m - 1);
    		cout << n << endl;
    	}
    	it++;
    }

    int opcao2;
    cout << endl;
    cout << "Indique o troco da estrada: ";
	while (!(cin >> opcao2) || opcao2 < 1 || opcao2 > indices.size()) {
		cout << "Opcao invalida! Escolha uma nova opcao: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	cin.clear();
	cin.ignore(1000, '\n');

    it = nomes_estradas.begin();
    advance(it, indices.at(opcao2 -1));
    string nome_rua = *it;
    bool rua_bloqueada = roadnetwork->getEdgeBlockedStatus(nome_rua);
    cout << endl;
    if(rua_bloqueada){
    	cout << "Esta estrada encontra-se cortada." << endl;
    }
    else{
    	cout << "Esta estrada encontra-se transitavel." << endl;
    }
    char ch;
    cout << "Deseja altera o estado da estrada? (Y/N): ";
    cin >> ch;
    cout << endl;
    switch(ch){
    case 'Y':
    	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
    	cout << "Estado da rua alterado com sucesso!" << endl;
    	break;
    case 'y':
       	roadnetwork->setEdgeBlocked(nome_rua, !rua_bloqueada);
       	cout << "Estado da rua alterado com sucesso!" << endl;
       	break;
    case 'n':
    	break;
    case 'N':
    	break;
    default:
    	cout << "Opcao invalida.";
    	break;
    }
    roadnetwork->writeEdgeFile();
    roadnetwork->updateInfo();
    returnMenu2();
}

void Interface::calculatePath(){
    cout << "-----------------" << endl;
    cout << "CALCULAR PERCURSO" << endl;
    cout << "-----------------" << endl;
    cout << endl;

    for(unsigned int i = 0; i < roadnetwork->getGraph().getVertexSet().size(); i++){
    	cout << i + 1 << ". " << roadnetwork->getGraph().getVertexSet().at(i)->getName() << endl;
    }
    int origem, destino;
    cout << endl;
    cout << "Indique a origem do percurso: ";
    cin >> origem;
    while(origem > roadnetwork->getGraph().getVertexSet().size() || origem < 1){
    	cout << "Opcão Inválida. Introduza uma nova origem: ";
    	cin.clear();
    	cin.ignore(1000, '\n');
    	cin >> origem;
    }
    cout << "Indique o destino do percurso: ";
    cin >> destino;
    while(destino > roadnetwork->getGraph().getVertexSet().size() || destino < 1){
    	cout << "Opcao Invalida. Introduza um novo destino: ";
    	cin.clear();
    	cin.ignore(1000, '\n');
    	cin >> destino;
    }

    origem = roadnetwork->getGraph().getVertexSet().at(origem - 1)->getInfo();
    destino = roadnetwork->getGraph().getVertexSet().at(destino - 1)->getInfo();

    this->roadnetwork->printPath(origem,destino);
    roadnetwork->updateInfo();
    returnMenu();
}

void Interface::showMap(){
	cout << "Mapa a ser gerado..." << endl;
	convertToGV();
	returnMenu();
}

void Interface::getAllCarsPath(){
    cout << "-------------------" << endl;
    cout << "PERCURSO DOS CARROS" << endl;
    cout << "-------------------" << endl;
    cout << endl;
	roadnetwork->printAllCarPath();
	returnMenu2();
}

void Interface::removeCar(){
    cout << "--------------" << endl;
    cout << "REMOVER CARRO" << endl;
    cout << "-------------" << endl;
    cout << endl;
    roadnetwork->printCarID();
    cout << endl;
    int opcao;
    cout << "Indique o numero do carro que deseja remover: ";
	while (!(cin >> opcao) || !roadnetwork->removeCar(opcao)) {
		cout << "Carro inexistente! Escolha um novo carro: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cin.clear();
	cin.ignore(1000, '\n');
    cout << endl << "Carro removido com sucesso." << endl;
    roadnetwork->writeCarsFile();
    roadnetwork->updateInfo();
	returnMenu2();
}

void Interface::evacuationRoute(){
    cout << "-----------------" << endl;
    cout << "ROTA DE EVACUACAO" << endl;
    cout << "-----------------" << endl;
    cout << endl;
    int opcao;
    cout << "Tipos de pesquisa: " << endl;
    cout << "[1] - Pesquisa Exata" << endl;
    cout << "[2] - Pesquisa Aproximada" << endl << endl;
    cout << "Escolha uma opcao: ";
    while (!(cin >> opcao) || opcao < 1 || opcao > 2) {
        cout << "Opcao Invalida! Escolha uma nova opcao: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    string estrada;
    cout << endl;
    if(opcao == 1){
		cout << "Introduza a sua localizacao exata: ";
		cin.clear();
		cin.ignore(1000, '\n');
		getline(cin, estrada);
		roadnetwork->exactEdgeSearch(estrada);
    }
    if(opcao == 2)
		approximateSearchAlgorithm();

    returnMenu2();
}

void Interface::approximateSearchAlgorithm() {
	cout << "-------------------" << endl;
	cout << "Pesquisa Aproximada" << endl;
	cout << "-------------------" << endl;
	cout << endl;

	int opcao;
	cout << "Algoritmo de pesquisa: " << endl;
	cout << "[1] - Edit Distance" << endl;
	cout << "[2] - Levenshtein" << endl << endl;
	cout << "Escolha uma opcao: ";
	while (!(cin >> opcao) || opcao < 1 || opcao > 2) {
		cout << "Opcao Invalida! Escolha uma nova opcao: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	string estrada;
	cout << "\nIntroduza a sua localizacao aproximada: ";
	cin.clear();
	cin.ignore(1000, '\n');
	getline(cin, estrada);

	if(opcao == 1)
		roadnetwork->approximateEdgeSearch(estrada, 1);
	if(opcao == 2)
		roadnetwork->approximateEdgeSearch(estrada, 2);

}

void Interface::closeMapWindow(){
	roadnetwork->closeMapWindow();
}

void Interface::returnMenu(){
	cout << endl;
	int opcao;
	cout << "[1] Voltar ao menu principal." << endl;
	cout << "[0] Sair" << endl;
	cout << endl;
	cout << "Escolha uma opcao: ";
	while (!(cin >> opcao) || opcao < 0 || opcao > 1) {
		cout << "Opcao invalida! Escolha uma nova opcao: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cin.clear();
	cin.ignore(1000, '\n');
	if(opcao == 1){
		this->closeMapWindow();
		cout << endl << "Voltando ao menu principal..." << endl << endl;
		sleep(1);
	}
	else if (opcao == 0){
		this->closeMapWindow();
		exit(0);
	}
}

void Interface::returnMenu2(){
	cout << endl;
	int opcao;
	cout << "[1] Voltar ao menu principal." << endl;
	cout << "[0] Sair" << endl;
	cout << endl;
	cout << "Escolha uma opcao: ";
	while (!(cin >> opcao) || opcao < 0 || opcao > 1 ) {
		cout << "Opcao invalida! Escolha uma nova opcao: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cin.clear();
	cin.ignore(1000, '\n');

	if(opcao == 1){
		cout << endl << "Voltando ao menu principal..." << endl << endl;
		sleep(1);
	}
	else if (opcao == 0){
		exit(0);
	}
}

void Interface::writeFiles()
{
	this->roadnetwork->writeCarsFile();
	this->roadnetwork->writeEdgeFile();
}
