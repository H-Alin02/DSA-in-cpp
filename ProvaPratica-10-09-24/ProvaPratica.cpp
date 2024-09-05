// Repository esterna con implementazioni di vari algoritmi e strutture dati
#include "DataStructures/Graph/HeaderFiles/WeightedGraph.h" // Struttura dati Grafo Pesato
#include "Algorithms/GraphAlgorithms/HeaderFiles/GraphAlgoithms.h" // Algoritmi su grafi, tra cui è presente una versione di dijkstra
#include <iostream>
#define GraphType AdjListWeightedGraph<int> // o AdjMatWeightedGraph<int>

GraphType getInputData(string path, int& source, int& destinazione);

int main() {

    int source, destinazione, result;

    // Crea 3 grafi di testing e li inizializza con i dati di input
    for(int i = 1; i <= 3; i++){

        // Crea un grafo pesato rappresentato da lista di adiacenze e lo inizializza con i dati di input
        GraphType graph = getInputData("inputs/input" + to_string(i) + ".txt", source, destinazione);
        cout << "Grafo " << i << ": " << endl;
        graph.print();

        // Leggi il nodo di partenza e di arrivo
        //cout << "Inserisci il nodo di partenza e di arrivo, per il grafo " << i << " : ";
        // cin >> source >> destinazione;

        // si applica l'algoritmo di Dijkstra e si stampa a console la soluzione
        result = GraphAlgorithms<int, GraphType>::dijkstra(source,destinazione,graph);
        cout << "Dijstra from " << source << " to " << destinazione << ": "<< result << "\n\n";

        // Scrivi il risultato su un file di output
        ofstream outfile("outputs/output" + to_string(i) + ".txt"); // Apri il file di output
        if (!outfile) {
            cerr << "Error opening output file" << endl;
            return 1;
        }
        outfile << "Dijkstra from " << source << " to " << destinazione << ": " << result << endl;

        // Chiudi il file di output
        outfile.close(); 
    }

    return 0;
}

GraphType getInputData(string path, int& source, int& destinazione) {

    int acquedotti, tubi;
    ifstream infile(path); 
    if(!infile){
        cerr << "Error opening file" << endl;
        exit(1);
    }

    // Leggi il numero di vertici, archi e nodi di partenza e di arrivo
    infile >> acquedotti >> tubi >> source >> destinazione;
    
    // Controllo sulla correttezza dell'input
    if(source < 0 || source >= acquedotti || destinazione < 0 || destinazione >= acquedotti){
        throw out_of_range("Invalid start or end node");
    }
    if(acquedotti < 2 || acquedotti > 200 || tubi < 0 || tubi > 5000){
        throw out_of_range("Invalid number of nodes or edges");
    }
        
    GraphType graph(acquedotti);

    // Aggiungi nuovi archi pesati al grafo
    int x, y;
    double z;
    for(int i = 0; i < tubi; ++i){
        infile >> x >> y >> z;
        if(z < 0 || z > 1000){
            throw out_of_range("Invalid edge weight");
        }
        graph.insert(x, y, z);
    }

    infile.close();

    return graph;
}
