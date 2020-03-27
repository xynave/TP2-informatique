#include "Graphe.h"
#include <fstream>
#include <queue>
#include <stack>
#include<map>

Graphe::Graphe(std::string cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if(!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    ifs >> m_estOriente;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'orientation du graphe.");
    }
    int ordre;
    ifs >> ordre;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'ordre du graphe.");
    }
    int taille;
    ifs >> taille;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de la taille du graphe.");
    }
    for(int i=0; i<ordre; ++i) {
        m_sommets.push_back(new Sommet(i));
    }
    int num1, num2;
    for(int i=0; i<taille; ++i) {
        ifs >> num1 >> num2;
        if(ifs.fail()) {
            throw std::runtime_error("Problème de lecture d'un.e arc/arête.");
        }
        m_sommets[num1]->addSuccesseur(m_sommets[num2]);
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
    }
}

Graphe::~Graphe() {
    for(auto addrSommet : m_sommets) {
        delete addrSommet;
    }
}

void Graphe::afficher() const {
    std::cout << std::endl << "Graphe ";
    std::cout << (m_estOriente ? "orienté" : "non orienté") << std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    std::cout << "Liste d'adjacences : " << std::endl;
    for(auto addrSommet : m_sommets) {
        addrSommet->afficher();
        std::cout << std::endl;
    }

}

// Algo parcoursBFS(s0)
std::vector<int> Graphe::BFS(int numero_s0) const {
    // 1. Tous les sommets sont blancs (non découverts)
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    // 2. Créer une file vide
    std::queue<const Sommet*> file;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    // 3. Enfiler s0 ; s0 devient gris
    file.push(m_sommets[numero_s0]);
    couleurs[numero_s0] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet* s;
    // 4. Tant que la file n’est pas vide :
    while(!file.empty()) {
        // 4.1 Défiler le prochain sommet s de la file (Traitement éventuel sur s)
        s = file.front();
        file.pop();
        // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
        for(auto succ : s->getSuccesseurs()) {
            if(couleurs[succ->getNumero()] == 0) { // blanc
                // 4.2.1 Enfiler s’; s’ devient gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                // 4.2.2 Noter que s est le prédécesseur de s’
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        // 4.3 s devient noir (exploré)
        couleurs[s->getNumero()] = 2;
    }
    return predecesseurs;
}






// Algo parcoursDFS(s0)
std::vector<int> Graphe::DFS(int numero_s0) const {
    // 1. Tous les sommets sont blancs (non découverts)
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    // 2. Créer une file vide
    std::stack<const Sommet*> file;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    // 3. Enfiler s0 ; s0 devient gris
    file.push(m_sommets[numero_s0]);
    couleurs[numero_s0] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet* s;
    // 4. Tant que la file n’est pas vide :
    while(!file.empty()) {
        // 4.1 Défiler le prochain sommet s de la file (Traitement éventuel sur s)
        s = file.top();
        file.pop();
        // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
        for(auto succ : s->getSuccesseurs()) {
            if(couleurs[succ->getNumero()] == 0) { // blanc
                // 4.2.1 Enfiler s’; s’ devient gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                // 4.2.2 Noter que s est le prédécesseur de s’
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        // 4.3 s devient noir (exploré)
        couleurs[s->getNumero()] = 2;
    }

    return predecesseurs;
}


// Algo parcoursConnexe
 std::map<int,std::vector<int>> Graphe::Connexe() const {
    int success=0;
    int numero_s0;
    int impaire;
    int nbrimpaire=0;
    std::vector<const Sommet*>ensemble;
    std::vector<int> nbrsommet;
    std::map<int,std::vector<int>> mape;
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    std::stack<const Sommet*> file;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);

 std::cout<<std::endl;
            for(int i=0;i<=m_sommets.size()-1;i++){
                if(couleurs[i]==0)
                {
                    numero_s0=i;
//DFS
                    file.push(m_sommets[numero_s0]);
                    couleurs[numero_s0] = 1;
                    const Sommet* s;
                    while(!file.empty()) {
                        s = file.top();
                        file.pop();
                        for(auto succ : s->getSuccesseurs()) {
                            if(couleurs[succ->getNumero()] == 0) {
                                file.push(succ);
                                couleurs[succ->getNumero()] = 1;

                            }
                        }
                        couleurs[s->getNumero()] = 2;
                        //Quand on le colorie on le met dans la chaine connexe correspondante
                        mape[success].push_back(s->getNumero()) ;
                    }
                    success++;
                }

    }
//affichage des connexes
     for(int i=0;i<success;i++)
     {
        std::cout<<"Composante connexe "<<i+1<<" : ";
                for(int j=0;j<mape[i].size();j++)
                {

                     std::cout<<mape[i][j]<<" ";
                }
        std::cout<<std::endl;
     }

 std::cout<<std::endl;
//cycle eulérien

//on calcule le nombre de liaison
for(auto addrSommet : m_sommets) {
        ensemble=addrSommet->getSuccesseurs();
       nbrsommet.push_back(ensemble.size());


    }

     for(int i=0;i<success;i++)
     {
         impaire=0;

                for(int j=0;j<mape[i].size();j++)
                {
                     if(nbrsommet[mape[i][j]]%2==1 )
                     {
                         impaire++;
                     }
                     if(nbrsommet[mape[i][j]]==0 )
                     {
                         impaire=100;
                     }

                }
                if(impaire==2 || impaire==0 )
                {
                  nbrimpaire++;

                }


     }
     std::cout<<"il y a "<<nbrimpaire<<" de chaine eulerienne"<<std::endl;
     std::cout<<std::endl;
 for(int i=0;i<success;i++)
     {
         impaire=0;

                for(int j=0;j<mape[i].size();j++)
                {
                     if(nbrsommet[mape[i][j]]%2==1)
                     {
                         impaire++;
                     }
                     if(nbrsommet[mape[i][j]]==0 )
                     {
                         impaire=100;
                     }

                }
                if(impaire==2 || impaire==0)
                {
                    std::cout<<"la chaine ";
                    for(int k=0;k<mape[i].size();k++)
                {

                     std::cout<<mape[i][k]<<" ";
                }
                std::cout<<" est eulerienne "<<std::endl;
                }


     }


 return mape;
}








