#include <string>
#include <vector>
#include <iostream>
#include "test.h"
#include "user.h"

/*
entrée:
	string s (la chaine de caracteres pour laquelle on veut compter le nombre de virgules)
description:
	Cette fonction compte le nombre de virgules dans une chaine de caracteres.
format retourné:
	pour les paramètres:
		string s "test,test,test,test"
	la fonction retourne:
		int 3
*/

int countNumFields(std::string &s){
    int ncommas = 0;
    for(char c: s)
        if(c == ',') ++ncommas;
    return ncommas;
}

/*
entrée:
    string l (la ligne qu'on veut séparer)
    string delim (le delimiteur de chaque champ)
description:
    Cette fonction sépare une chaine de caractères donnée en plusieurs
    champs en utilisant un delimiteur donné. Elle retourne un vecteur de 
	chaines de caractères.
format retourné:
	pour les paramètres:
		string l "xyz,zyx"
		string delim ","
	la fonction retourne:
		vector<string> {"xyz", "zyx"}
*/

std::vector<std::string> lineSplitter(std::string l, std::string delim){
    std::vector<std::string> line;
    int currPos;

    //l.find retourne l'indice de la première occurance d'un caractère donné
    currPos = l.find(delim);
    while(currPos != -1){ // jusqu'à ce qu'on ne puisse plus trouver ce caractère
        line.push_back(l.substr(0, currPos));
        l.erase(0, currPos+1);
        currPos = l.find(delim);
    }
    line.push_back(l); // envoyer ce qu'il reste

    return line;
}

/*
entrée:
    vector<User> &u (vecteur contenant les joueurs)
description:
    Cette fonction enchaîne les défis entre les joueurs de manière
    itérative en utilisant la fonction User::pointCounter.
format retourné:
    rien
*/

void play(std::vector<User> &u){
    for(int i = 0; i < u.size(); ++i){
        for(int j = i+1; j < u.size(); ++j){
            u[i].pointCounter(u[j]);
        }
    }
}

/*
entrée:
    ostream &html (sortie standard pour le fichier html)
    vector<User> &users (vecteur contenant les joueurs)
description:
    Cette fonction construit la page HTML en utilisant les données
    fournies par les fonctions membres de la classe User
format retourné:
    rien
*/

void pageBuilder(std::ostream& html, std::vector<User>& users){
	int counter = 0;
	int place = 1;
	while(counter < users.size()){
		if(counter != 0){
			if(users[counter-1].getPoints() != users[counter].getPoints()) place = counter+1;	
		}
		html << "						<tr class='"; 
		switch(place){
			case 1: html << "one"; break;
			case 2: html << "two"; break;
			case 3: html << "three"; break;
			default: html << "other";
		}
		html << "'>" << std::endl;
        html << "							<td class='category'>Classement</td>" << std::endl;
		html << "							<td>" << place << "</td>" << std::endl;
        html << "							<td class='category'>Distinction</td>" << std::endl;
		html << "							<td><span";
        if(place == 1){
            html << " title='" << users[counter].pseudonym() << " a le plus de points, il/elle repart premier de cette saison !" << "'>🥇";
        } else if (place == 2) {
            html << " title='" << users[counter].pseudonym() << " talonne " << users[counter-1].pseudonym() << ", il/elle repart second de cette saison !" << "'>🥈";
        } else if (place == 3) {
            html << " title='" << users[counter].pseudonym() << " entre dans la course à la première place, il/elle repart troisième de cette saison !" << "'>🥉";
        } else if (place == users.size()){
            html << " title='" << users[counter].pseudonym() << " est un pacifique, il/elle a souvent laissé gagné son adversaire !" <<  "'>🕊️";
        } else if (users[counter].hasMostDraws()) {
            html << " title='" << users[counter].pseudonym() << " est un résistant, il/elle a accumulé le plus d`égalités !" <<  "'>🛡️";
        } else if (place <= 5) {
            html << " title='" << users[counter].pseudonym() << " reçoit une belle trophée de participation pour son valant effort !" <<  "'>🏆";
        } else {
            html << ">‏‏‎⠀‎";
        }
		html << "</span></td>" << std::endl;
        html << "							<td class='category'>Joueur</td>" << std::endl;
        html << "							<td><img alt='Image du joueur' width='135' height='135' src='";
        if(users[counter].hasImage()) html << "https://projet.iut-orsay.fr/photos/" << users[counter].username() << ".jpg";
        else html << "./anon.png";
        html << "'></td>" << std::endl;
		html << "							<td>" << users[counter].pseudonym() << "</td>" << std::endl;
        html << "							<td class='category'>Points</td>" << std::endl;
		html << "							<td>" << users[counter].getPoints() << "</td>" << std::endl;
        html << "							<td class='category'>Victoires</td>" << std::endl;
		html << "							<td>" << users[counter].getWin() << "</td>" << std::endl;
        html << "							<td class='category'>Défaites</td>" << std::endl;
		html << "							<td>" << users[counter].getLoss() << "</td>" << std::endl;
        html << "							<td class='category'>Egalités</td>" << std::endl;
		html << "							<td>" << users[counter].getDraws() << "</td>" << std::endl;
        html << "							<td class='category'>Stratégie</td>" << std::endl;
		html << "							<td>" << users[counter].strat_string() << "</td>" << std::endl;
		html << "						</tr>" << std::endl;
		++counter;
	}
}

/*
entrée:
    (mergeSortVec)
    vector<User> &vec (vecteur contenant les joueurs)
    (merge)
    vector<User> &vec1 (partie du vecteur contenant les joueurs)
    vector<User> &vec2 (partie du vecteur contenant les joueurs)
description:
    Cette fonction, ainsi que merge, composent le tri fusion de
    la liste des joueurs, à fin d'obtenir les classements.
    Ce tri est dans l'ordre établie par l'operand > (voir user.cpp).
format retourné:
    vector<User>: (vecteur contenant les joueurs trié)
*/

std::vector<User> mergeSortVec(const std::vector<User> &vec)
{
    if(vec.size() <= 1)
        return vec;

    std::vector<User> vec1;
    std::vector<User> vec2;

    int i = 0;
    for(; i < vec.size()/2; ++i)
        vec1.push_back(vec[i]);
    for(; i < vec.size(); ++i)
        vec2.push_back(vec[i]);

    std::vector<User> vect1 = mergeSortVec(vec1);
    std::vector<User> vect2 = mergeSortVec(vec2);

    return merge(vect1, vect2);
}

std::vector<User> merge(std::vector<User> &vec1, std::vector<User> &vec2)
{
    if(vec1.size() == 0)
        return vec2;
    if(vec2.size() == 0)
        return vec1;

    std::vector<User> ret;

    int k1 = 0;
    int k2 = 0;

    while(k1 < vec1.size() && k2 < vec2.size())
    {
        if(vec1[k1] > vec2[k2])
        {
            ret.push_back(vec1[k1]);
            k1++;
        } else {
            ret.push_back(vec2[k2]);
            k2++;
        }
    }

    for(; k1 < vec1.size(); k1++)
        ret.push_back(vec1[k1]);

    for(; k2 < vec2.size(); k2++)
        ret.push_back(vec2[k2]);

    return ret;
}

/*
entrée:
    vector<User> &users (vecteur contenant les joueurs)
description:
    Cette fonction trouve le joueur avec le plus d'égalités
	pour l'achievement "plus d'égalités";
format retourné:
    rien
*/

void mostDrawsFinder(std::vector<User> &users){
	int current_user = 0;
	int currnumdraws = users[0].getDraws();
	for(int i = 1; i < users.size(); ++i){
		if(users[i].getDraws() > currnumdraws){
			currnumdraws = users[i].getDraws();
			current_user = i;
		}
	}
	users[current_user].setMostDrawstoTrue();
}