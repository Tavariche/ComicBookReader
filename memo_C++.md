#C++

##INCLUDES
* `iostream` -> Fonctionnalités de base (affichage, ...)
* `string` -> Chaînes de caractères
* `cmath`	-> Fonctions de math
* `vector` -> Tableaux dynamiques
* `fstream` -> Fichiers
* `using namespace std;` -> Utilise l'espace de noms std par défaut



##STRUCTURES DE CONTROLE
* `if(cond) {} else if (cond) {} else {}`	-> Condition si
* `switch(i){case n:...; break;}` -> Switch suivant les valeurs de i
* `while (cond) {}` -> Boucle "tant que cond vrai"
* `do {} while (cond`) -> Boncle faire puis continuer tant que cond vrai
* `for(init ; cond ; op)`	-> boucle for



##FONCTIONS
* `void myFunction(int& i)` -> L'argument est reçu par référence (modifiable)
* `void myFunction(int const& i)`	-> Passage par ref constante (pas de modif possible)
* `void myfunction(int i, int j = 42)` -> Dernier argument facultatif, valeur par defaut 42
	* Arguments facultatifs à la fin obligatoire
	* Uniquement dans le PROTOTYPE !



##TABLEAUX
* `int t[3] = {1, 2, 3}` -> Tableau de 3 cases initialisé
* `vector<int> t(3,0)` -> Tableau dynamique de 3 cases init à 0 (0 case possible)
* `tab.push_back(x)` -> Insère x à la fin de tab
* `tab.pop_back()` -> Supprime la dernière case de tab
* `tab.size()` -> Renvoie la taille de tab
* `int t[x][y]` -> Tableau multidimensionnel
* `vector<vector<int> > grid` -> Tableau multidimensionnel dynamique (bof)



##FICHIERS
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



##POINTEURS
* `int* p` -> Pointeur sur int
* `*p` -> Valeur stockée dans la case pointée
* `&i` -> Adresse de i
* `new int` -> Renvoie un pointeur vers une case int
* `delete pointeur` -> libère la mémoire pointée



##CHAINES
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



##CLASSES
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




##DIVERS
* `std::cout <<` -> Affichage
* `<< std::endl` -> Fin de ligne
* `bool`, `char`, `int`, `unsigned`, `double`, `string` -> Types courants
* `int& i(j)` -> `j` est une référence à `i`
* `std::cin >> i` -> Lire une valeur à stocker dans `i`
* `getline(cin, x)` -> Stocke la ligne lue complète dans `x`
* `std::cin.ignore()` -> A placer entre un `cin >>` et un `getline`
* `int const x` -> Constante `x`

----------------

#Qt

##Code minimal

	#include <QApplication>
	 
	int main(int argc, char *argv[])
	{
	    QApplication app(argc, argv);
	    return app.exec();
	}

Ajouter au fichier .pro la ligne `QT += widgets`

##Généralités

* `#include <QtWidgets>` -> Pour être tranquille
* `Element.show()` -> Afficher un élément
* `element.attribut()` -> Accesseur de lecture d'attribut
* `element.setAttribut()` -> Accesseur d'écriture d'attribut
* `QCoreApplication::applicationDirPath() + "/chemin"` -> chemin relatif universel


##Quelques elements courants

###QFont

* `QFont maPolice("police", ~taille, ~gras(0..99), ~italic(true/false))` -> Objet de police de texte


###QPushButton

* `QPushButton bouton("nomBoutton", &Parent)` -> Créer un bouton contenu par parent
* `bouton.setToolTip("monInfobulle")` -> Renseigner l'infobulle
* `bouton.setFont(QFont)` -> Changer la police
* `bouton.setCursor(Curseur)` -> Changer le curseur lors du survol ([liste](http://qt-project.org/doc/qt.html#CursorShape-enum))
* `bouton.setIcon(QIcon("Chemin"))` -> Changer l'icône du bouton
* `bouton.shortcut(RaccourciClavier)` -> Définit le raccourci clavier correspondant au bouton
* `bouton.move(x, y)` : Déplacer le bouton
* `bouton.setGeometry(x, y, l, h)` -> Définit la position et les dimentions du bouton


##Création d'une fenêtre

**Héritage obligatoire !**

	class MaFenetre : public QWidget
	{}

Les éléments de la fenêtre sont pointés et alloués dans le constructeur

La destruction des éléments d'un widget est automatique dans Qt

##Evenements et slots

Utiliser la méthode statique suivante :

	QObject::connect(*emetteur, SIGNAL(signal()), *recepteur, SLOT(slot())

* `qApp` -> Pointeur vers l'application principale créé automatiquement
* `public slots:` -> Environnement des slots personnalisés d'un objet
* `signals:` -> Environnement des signals personnalisés d'un objet
	* On implémente pas un signal
	* un signal renvoit toujours void et passe ses arguments au slot connecté
	* écrire `emit monSignal()` là où le signal doit être émis