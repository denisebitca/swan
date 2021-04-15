#include <iostream>
#include <vector>
#include <string>
#include "user.h"
#include "test.h"

// constructor


/*
entrée:
	vector<string> fields (champs retournés par la fonction lineSplitter)
	vector<int> counting (vecteur contenant les valeurs de chaque tâche pour chaque défi entre deux joueurs)
description:
	Cette fonction est le constructeur de la classe User. Elle initialise les données membre de la classe.
format retourné:
	rien
*/
User::User(std::vector<std::string> fields, std::vector<int>& counting){
    this->un = fields[0]; //nom d'utilisateur
    this->pn = fields[1]; //pseudonyme
    this->img = fields[2]; //image (0 pour non, 1 pour oui)
    this->strategy = fields[3]; // stratégie
    this->pointscheme = counting; // vecteur des valeurs par tache
}

// getters


// nom d'utilisateur
std::string User::username() const{
    return this->un;
}

// pseudonyme
std::string User::pseudonym() const{
    std::string ps = this->pn;
	/*
		Les pseudos sont insérés dans les balises HTML correspondantes aux "achievements":
		<span title='(...)Jonathan est rentré en première(...)'>
		
		S'il y a un pseudo qui contient le caractère ', l'attribut se fermera plus tôt que
		prévu : <span title='(...)N'golo est rentré en première(...)'>
		
		Cette boucle remplace toutes les occurances de ' par ` pour éviter ce problème.
	*/
    for(int i = 0; i < ps.size(); ++i){
        if(ps[i] == '\'') ps[i] = '`';
    }
    return ps;
}

// si le joueur a une image ou non
bool User::hasImage() const{
    return this->img=="1"?true:false;
}

// la stratégie
/*
	description:
		Cette fonction est presque identique à lineSplitter(). Cependant, elle utilise int à la place de string,
		et elle utilise "|" entant que delimiteur. En plus, elle compte le nombre de champs crées parce que sur
		certains fichiers de stratégie (notamment strategie_saison1.csv), il y a un caractère | à la fin en trop.
*/
std::vector<int> User::strat() const{

    std::string delim = "|";
    std::string l = this->strategy;
    std::vector<int> a;
    int currPos;
    int numMatch = 0;

    currPos = l.find(delim);
    while(currPos != -1 && numMatch != 7){
        a.push_back(std::stoi(l.substr(0, currPos)));
        l.erase(0, currPos+1);
        currPos = l.find(delim);
        numMatch++;
    }

    if(l.find(delim) != -1) l.pop_back();
    a.push_back(std::stoi(l));

    return a;
}

// la chaine de caractere de la stratégie
/*
	description:
		Cette fonction existe pour la fonction pageBuilder : 
		elle retourne la chaine de caractere correspondante à 
		la stratégie pour pouvoir la montrer sur la page HTML
*/
std::string User::strat_string() const{
	return this->strategy;
}
// nombre de points
int User::getPoints() const{
    return (this->wins*2) + this->draws;
}
// nombre de victoires
int User::getWin() const{
    return this->wins;
}
// nombre d'égalités
int User::getDraws() const{
    return this->draws;
}

// nombre de pertes
int User::getLoss() const{
    return this->loss;
}

// si ce joueur a le plus d'égalités
bool User::hasMostDraws() const{
	return this->hmd;
}

// setters

// nombre de victoires
void User::addWin(){
    ++this->wins;
}

// nombre d'égalités
void User::addDraw(){
    ++this->draws;
}

// nombre de pertes
void User::addLoss(){
    ++this->loss;
}

// si ce joueur a le plus d'égalités
void User::setMostDrawstoTrue(){
	this->hmd = true;
}

// autres fonctions membres

/*	
	entrée:
		User u2 (le joueur contre lequel ce joueur s'affronte)
	description:
		Cette fonction détermine qui gagne entre deux joueurs.
	jeu d'essai:
		pointscheme: 1|1|1|1|1|1|1|1
		
		stratégie de l'utilisateur 1 : 
		6|7|8|0|8|8|11|16
		
		stratégie de l'utilisateur 2 :
		6|10|5|0|12|7|16|8
		
		boucle for:
			0: 6 = 6 donc personne n'a pas de points;
			1: 7 < 10 donc p2 (points de l'utilisateur 2) = 1
			2: 8 > 5 donc p1 = 1
			(...)
			7: 16 > 8 donc p1 = 3 et p2 = 3
			
		comparaisons:
			p1 = p2 donc c'est une égalité.
			u1.draws += 1;
			u2.draws += 1;

*/
void User::pointCounter(User &u2){
    std::vector<int> strat1 = this->strat();
    std::vector<int> strat2 = u2.strat();
    int p1 = 0, p2 = 0;
    for(int i = 0; i < 8; i++){
        if(strat1[i] > strat2[i]) p1 += this->pointscheme[i];
        else if (strat2[i] > strat1[i]) p2 += this->pointscheme[i];
    }
    if(p1>p2){
        this->addWin();
        u2.addLoss();
    } else if (p2>p1){
        this->addLoss();
        u2.addWin();
    } else {
        this->addDraw();
        u2.addDraw();
    }
}

// operator
/*
	description:
		Pour qu'un joueur soit placé au dessus d'un autre joueur, il faut qu'il ait plus de points.
		Puis, au niveau du placement lorsqu'ils sont au même rang, s'ils ont la même quantité de points,
		il faut qu'il ait plus de victoires.
		S'ils ont le même nombre de victoires, il faut ensuite que le joueur ait plus d'égalités.
		En fin, s'ils ont le même nombre d'égalités, on suppose qu'ils ont le même nombre de pertes,
		alors on les met dans l'ordre alphabetique.
*/

bool User::operator>(const User &u2){
	if(this->getPoints() > u2.getPoints()) return true;
	else if (this->getPoints() == u2.getPoints()){
		if(this->getWin() > u2.getWin()) return true;
		else if(this->getWin() == u2.getWin()){
			if(this->getDraws() > u2.getDraws()) return true;
			else if(this->getDraws() == u2.getDraws()){
				//EDGE CASE (!) - if all is equal, order numerically, then alphabetically by username, regardless of string length
				//this part adds all the ascii characters together, then divides them by length (so that there is no string length bias)
				int user1ascii = 0;
				int user2ascii = 0;
				for(char c: this->username()) user1ascii += (int)tolower(c);
				for(char c: u2.username()) user2ascii += (int)tolower(c);
				return user1ascii/this->username().size() < user2ascii/u2.username().size();
			}
		}
	}
	return false;
}

// debougage

std::ostream& operator<<(std::ostream &os, const User &u){
    os << u.username() << "\t\t" << u.pseudonym() << "\t\t" << (u.hasImage()?"a une image":"n'a pas d'image") << "\t\t" << std::endl;
    for(int i: u.strat()) os << i << "\t";
    os << std::endl << "Points: " << u.getPoints() << std::endl;
    os << "W: " << u.getWin() << std::endl;
    os << "D: " << u.getDraws() << std::endl;
    os << "L: " << u.getLoss() << std::endl;
    return os;
}
