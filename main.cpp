#include <iostream>
#include "Graphe.h"

void afficherParcours(size_t s0, const std::vector<int>& precesseur) {
    for(size_t i = 0; i < precesseur.size(); ++i) {
        if (i != s0) {
            if(precesseur[i] != -1) {
                std::cout << i << " <--- ";
                size_t j = precesseur[i];
                while(j != s0) {
                    std::cout << j << " <--- ";
                    j = precesseur[j];
                }
                std::cout << j << std::endl;
            }
        }
    }
}



int main() {
    size_t s0 = 0;
    Graphe g{"graphe-no-1.txt"};
    std::vector<int> arborescence;
       std::map<int,std::vector<int>> mape;
    g.afficher();

    std::cout << std::endl << "BFS : Veuillez saisir le numéro du sommet initial pour la recherche du plus court chemin : ";
    std::cin >> s0;
    arborescence = g.BFS(s0);
    std::cout << "Plus courts chemins depuis le sommet " << s0 << " (BFS) : " << std::endl;
    afficherParcours(s0, arborescence);


     std::cout << std::endl << "DFS : Veuillez saisir le numéro du sommet initial pour la recherche du plus court chemin : ";
    std::cin >> s0;
    arborescence = g.DFS(s0);
    std::cout << "Plus courts chemins depuis le sommet " << s0 << " (DFS) : " << std::endl;
    afficherParcours(s0, arborescence);



     mape =g.Connexe();




    return 0;
}
