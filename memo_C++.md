#C++

[Une bonne doc de la SL](http://www.cplusplus.com/reference/)

##Bibliothèques
* `iostream` -> Fonctionnalités de base (affichage, ...)
* `string` -> Chaînes de caractères
* `cmath`	-> Fonctions de math
* `fstream` -> Fichiers
* `cctype` -> Manipulation de caractères
* `ctime` et `cstdlib` -> Surtout pour rand() et srand(time(0))




##Structures de controle
* `if(cond) {} else if (cond) {} else {}`	-> Condition si
* `switch(i){case n:...; break;}` -> Switch suivant les valeurs de i
* `while (cond) {}` -> Boucle "tant que cond vrai"
* `do {} while (cond`) -> Boncle faire puis continuer tant que cond vrai
* `for(init ; cond ; op)`	-> boucle for



##Fonctions
* `void myFunction(int& i)` -> L'argument est reçu par référence (modifiable)
* `void myFunction(int const& i)`	-> Passage par ref constante (pas de modif possible)
* `void myfunction(int i, int j = 42)` -> Dernier argument facultatif, valeur par defaut 42
	* Arguments facultatifs à la fin obligatoire
	* Uniquement dans le PROTOTYPE !



##Tableaux
* `int t[3] = {1, 2, 3}` -> Tableau de 3 cases initialisé
* `vector<int> t(3,0)` -> Tableau dynamique de 3 cases init à 0 (0 case possible)
* `tab.push_back(x)` -> Insère x à la fin de tab
* `tab.pop_back()` -> Supprime la dernière case de tab
* `tab.size()` -> Renvoie la taille de tab
* `int t[x][y]` -> Tableau multidimensionnel
* `vector<vector<int> > grid` -> Tableau multidimensionnel dynamique (bof)



##Fichiers
* `ofstream monFlux("chemin rel/abs")` -> ouverture de fichier en écriture, créé si inexistant
* `ofstream ............", ios::app)` -> Ouverture en mode d'ajout en fin de fichier
* `ifstream monFlux("chemin")` -> Ouverture de fichier en lecture
* `getline(monFlux, ligne)` -> Lit une ligne à stocker dans ligne, false fin de fichier
* `monFlux >> x` -> Lit un mot et le convertit dans le type x
* `monFlux.get(a)` -> Lit un caractère et le stocke dasn a
* `monFlux.close()` -> Fermeture du fichier (facultatif)
* `monFlux.open()` -> Ouverture retardée du fichier
* `monFlux.tellg()/tellp()` -> Indique la position du curseur (lecture / écriture)
* `monFlux.seekg(n, pos)/seekp(n, pos)` -> Déplacer le curseur de n depuis pos
	* `pos = ios::beg` -> Début du fichier
	* `pos = ios::endl` -> Fin du fichier
	* `pos = ios::cur` -> Position actuelle
* Taille du fichier : aller à la fin et demander la position (donnée en octets)



##Pointeurs
* `int* p` -> Pointeur sur int
* `*p` -> Valeur stockée dans la case pointée
* `&i` -> Adresse de i
* `new int` -> Renvoie un pointeur vers une case int
* `delete pointeur` -> libère la mémoire pointée



##Chaines
* `string chaine("init")` -> Crée un objet chaîne de caractères
* `chaine1 + chaine2` -> Renvoie la concaténation des deux chaînes
* `== / !=` -> Tests d'égalité entre chaînes
* `chaine.c_str()` -> Renvoie la chaîne contenue dans l'objet de type string
* `chaine.erase(i,j)`	-> Retire j lettre à partir de la ieme
* `chaine.erase()` -> Supprime tous les caractères
* `chaine.size()` -> Longueur de la chaîne
* `chaine.substr(x, n)` -> Extrait n caractère à partir du x-ième (départ à 0)
	* n facultatif, extrait toute la fin si pas spécifié
* `chaine.c_str()` -> Renvoie un pointeur sur la chaîne de caractère elle-même



##Classes
* `class MaClasse {};` -> Déclaration d'une classe (attributs + méthodes)
* `private :` -> Accessible depuis l'objet seulement
* `public :` -> Accessible par tous
* `protected :` -> Accessible par les classes filles
* `MaClasse(args): i(j), ... {}` -> Constructeur de classe
	* Un constructeur de copie existe par défaut, il copie tout même les pointeurs /!\
	* Explicit devant évite son utilisation automatique
* `~MaClasse(){}` -> Destructeur de classe
* `void maMethode() const {}` -> Méthode constante (ne modifie aucun paramètre)
* Surcharge d'opérateurs -> Hors classe si pas de modif d'objet
	* `bool operator==(Obj const& a, ...)` -> Surcharge de `==`, idem pour `!=`, `<`, `<=`, `>`, `>=`
	* `Obj operator+(Obj const& a, ...)` -> Surcharge de `+`, idem pour `-`, `*`, `/`, `%`
	* `Obj& operator+=(Obj const& a)` -> Surcharge de `+=`, idem pour `-=`, `*=`, `/=`
		* /!\ A placer dans l'objet (modif de l'obj)
	* [Surcharge de `<<`](https://openclassrooms.com/courses/programmez-avec-le-langage-c/la-surcharge-d-operateurs#/id/r-1897890)
* `this` -> Attribut pointant sur l'objet lui-même
* `class Classe1 : public Classe2` -> Classe1 hérite de Classe2
* `virtual function()` -> Fonction virtuelle permettant le polymorphisme
	* Toujours faire un destructeur virtuel si polymorphisme
* `virtual function() = 0` -> Pour fonction virtuelle pure inutilisable
	* La classe devient abstraite : plus de création d'objet de cette classe possible
* On peut créer un tableau de pointeurs sur ClasseMere pour stocker des Classefille différentes.
	* Possibilités de polymorphisme par la suite
* `static function()` -> Fonction statique d'une classe. Permet son utilisation sans créer l'objet avec `Classe::founction()`
* `static int i` -> Attribut statique : accessible partout dans le code	
	* Initialiser par une ligne hors de toute fonction dans le .cpp
* `friend function()` -> Fonction amie ayant accès à tout ce que contient l'objet dans lequel est mis le prototype


##Conteneurs

###liste des conteneurs standards

`#include` le nom du conteneur pour s'en servir

* `vector` -> Tableaux dynamiques
* `deque` -> Comme `vector` avec ajouts au début possible
* `stack` -> Pile donc accès seulement en haut
* `queue` -> Structure FIFO
* `priority_queue` -> Stockage d'éléments classables (`operator<` requis)
* `map<indice, element>` -> Table Associative dont les éléments sont indexées par des variables de type indice
	* `multimap` -> Chaque clé peut exister plusieurs fois
* `set` -> Comme map mais clé = élément
	* `multiset` -> Chaque clé peut exister plusieurs fois

**Choix du conteneur**
![Schéma de choix du conteneur](https://user.oc-static.com/files/313001_314000/313596.png)

###Méthodes communes quand possible

* `size()` -> Taille du conteneur
* `empty()` -> Indique si le conteneur est vide
* `clear()` -> Vider le conteneur
* `swap()` -> Echanger le contenu de deux conteneurs (même types)
* Séquences :
	* `push_back()` -> Ajout à la fin
	* `pop_back()` -> Retrait à la fin
	* `push_front()` -> Ajout au début
	* `pop_front()` -> Retrait au début
	* `assign(val)` -> Remplir la séquence avec val
	* `push(), pop(), top()` -> Ajouter, retirer ou consulter le haut d'une pile ou queue avec priorité

###Accesseurs

* `typeConteneur::iterator` -> Déclaration itérateur
* `conteneur.begin()` -> Itérateur sur le premier élément
* `conteneur.end()` -> Itérateur sur le dernier élément + 1
* `conteneur.insert(iterateur, element)` -> Ajout de `element` avec `iterateur`
* `conteneur.erase(iterateur)` -> Supprime l'élément itéré

##Divers

* `using namespace std;` -> Utilise l'espace de noms std par défaut
* `std::cout <<` -> Affichage
* `<< std::endl` -> Fin de ligne
* `bool`, `char`, `int`, `unsigned`, `double`, `string` -> Types courants
* `int& i(j)` -> `j` est une référence à `i`
* `std::cin >> i` -> Lire une valeur à stocker dans `i`
* `getline(cin, x)` -> Stocke la ligne lue complète dans `x`
* `std::cin.ignore()` -> A placer entre un `cin >>` et un `getline`
* `int const x` -> Constante `x`