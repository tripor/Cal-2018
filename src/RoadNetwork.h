#ifndef SRC_ROADNETWORK_H_
#define SRC_ROADNETWORK_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include "Graph.h"
#include "graphviewer.h"
#include "Utils.h"

/**
 * Cor padrao dos vertices
 */
#define DEFAULT_VERTEX_COLOR "blue"
/**
 * Cor das edges com pouco transito
 */
#define DEFAULT_EDGE_COLOR "green"
/**
 * Cor dos vertices que estao a ser representados como percurso
 */
#define HIGHLIGHTED_VERTEX_COLOR "yellow"
/**
 * Cor das edges que estao a ser representadas como percurso
 */
#define HIGHLIGHTED_EDGE_COLOR "yellow"
/**
 * Cor das edges com algum transito
 */
#define MEDIUM_TRAFFIC "orange"
/**
 * Cor das edges com muito transito
 */
#define HIGH_TRAFFIC "red"
/**
 * Cor das edges bloqueadas
 */
#define BLOCKED_EDGE_COLOR "black"

/**
 * Classe que guarda todas as informacoes necessarias, que faz todos os calculos
 * necessarios com essas informacoes e atualiza o graphviewer
 */
class RoadNetwork {
private:
	/**
	 * Variavel que guarda o grafo
	 */
	Graph<int> graph;
	/**
	 * Variavel que guarda o graphviewer
	 */
	GraphViewer *gv;
public:
	/**
	 * Construtor
	 */
	RoadNetwork();
	/**
	 * Destrutor
	 */
	virtual ~RoadNetwork();
	/**
	 * Le os ficheiros com informacao relativa aos vertices, as edges e aos carros
	 * e atualiza o grafo com essa informacao
	 */
	void readOSM();
	/**
	 * Escreve a informacao das edges no ficheiro correspondente
	 */
	void writeEdgeFile();
	/**
	 * Converte a informacao contida no grafo numa do tipo graphviewer
	 */
	void convertToGV();
	/**
	 * Devolve o grafo
	 * @return grafo
	 */
	const Graph<int>& getGraph() const;
	/**
	 * Indica se uma estrada se encontra bloqueada ou nao
	 * @param name nome da estrada que se pretende verificar
	 * @return true se estiver bloqueada, false se nao
	 */
	bool getEdgeBlockedStatus(string name);
	/**
	 * Altera o estado de bloqueada, ou nao, de uma estrada
	 * @param edge_name nome da estrada que se pretende alterar
	 * @param blocked novo valor
	 */
	void setEdgeBlocked(string edge_name, bool blocked);
	/**
	 * Devolve o peso total de um percurso
	 * @param vec vetor com os vertices do percurso a calcular
	 * @return valor do peso do percurso
	 */
	double getWeightOfPath(vector<Vertex<int>*> vec);
	/**
	 * Imprime a informacao relativa a um percurso, atualizando, tambem, o graphviewer
	 * com. Adiciona um novo carro ao programa cada vez que é executada.
	 * @param nodeStartID
	 * @param nodeDestinationID
	 */
	void printPath(int nodeStartID, int nodeDestinationID);
	/**
	 * Imprime o percurso completo de todos os carros
	 */
	void printAllCarPath() const;
	/**
	 * Imprime o inicio e o fim do percurso de todos os carros
	 */
	void printCarID() const;
	/**
	 * Remove um carro do programa
	 * @param id id do carro a remover
	 * @return true so foi possivel remover, falso se nao
	 */
	bool removeCar(int id);
	/**
	 * Escreve a informacao relativa a todos os carros no ficheiro
	 */
	void writeCarsFile();
	/**
	 * Atualiza a cor de um vertice no graphviewer para amarelo (percurso)
	 * @param id id do vertice a atualizar
	 */
	void highlightNode(int id) const;
	/**
	* Atualiza a cor de uma edge no graphviewer para amarelo (percurso)
	* @param id id da edge a atualizar
	*/
	void highlightEdge(int id) const;
	/**
	 * Atualiza a cor das edges tendo em conta o numero de carros que por ela circulam
	 * e se se encontra bloqueada ou nao
	 */
	void updateMap() const;
	/**
	 * Fecha a janela do graphviewer
	 */
	void closeMapWindow() const;
	/**
	 * Atualiza o conteudo do grafo
	 */
	void updateInfo();
	/**
	 * Procura exata das estradas
	 * @param estrada localização introduzida
	 */
	void exactEdgeSearch(string estrada);
	/**
	 * Procura aproximada das estradas
	 * @param estrada localização introduzida
	 * @param op opção entre o método de Levenshtein ou Edit Distance
	 */
	void approximateEdgeSearch(string estrada, int op);
	/**
 	 * Pré-processamento do padrão
 	 * @param pattern expressão a procurar
	 * @return valor do deslocamento a utilizar no algoritmo de Knuth-Morris-Pratt
 	*/
	vector<int> cpf(string pattern);
	/**
	 * Algoritmo de Knuth-Morris-Pratt
	 * @param text texto onde vai ser procurada a expressão
	 * @param pattern expressão a procurar
	 * @return número de vezes que podemos encontrar a expressão pattern em text
	 */
	int kmpMatcher(string text, string pattern);
	/**
 	 * Algoritmo de Pesquisa Aproximada Edit Distance
 	 * @param pattern expressão a procurar
 	 * @param text texto onde vai ser procurada a expressão
 	 * @return número mínimo de operações necessárias para transformar uma expressão na outra
 	 */
	int editDistance(string pattern, string text);
	/**
 	 * Algoritmo de Levenshtein
 	 * @param s1 expressão a comparar
 	 * @param s2 expressão a comparar
 	 * @return número mínimo de operações necessárias para transformar uma expressão na outra
 	 */
	unsigned int levenshtein(const string & s1, const string & s2);
};

#endif /* SRC_ROADNETWORK_H_ */

