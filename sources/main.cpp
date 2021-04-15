#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include "user.h"
#include "test.h"


using namespace std;

int main(int argc, char **argv)
{
    vector<User> users; // vector contenant les joueurs
	int season; // nombre de la saison Swan
	string season_slogan; // la devise de la saison Swan
    vector<int> point_scheme; // vecteur qui contient la valeur de chaque tâche
	int linenum = 0; //nombre de lignes traitées
	
	if(argc != 2 || (string)argv[1] == "--help" || (string)argv[1] == "-h"){
		cout << "\nUsage: " << argv[0] << " [FICHIER DE STRATEGIES SWAN CSV]" << endl;
		cout << "\nOptions: -h (ou --help) (obtenir cet affichage)" << endl;
		cout << "\nCe logiciel transforme un fichier de strategies de plusieurs joueurs dans un fichier HTML qui classe ces joueurs." << endl;
		cout << "\nLa première ligne du fichier de stratégies doit être dans ce format." << endl;
		cout << "n1|n2|n3|n4|n5|n6|n7|n8,numSaison,devise_de_la_saison" << endl;
		cout << "\tAvec n1 à n8 qui veut dire le nombre de points par tâche (chiffres)" << endl;
		cout << "\tnumSaison qui est le nombre de la saison Swan (chiffre)" << endl;
		cout << "\tdevise_de_la_saison qui est une chaîne de caractères" << endl;
		cout << "\nLes lignes qui suivent doivent être dans ce format :" << endl;
		cout << "nomutilisateur,pseudo,Image?,n1|n2|n3|n4|n5|n6|n7|n8" << endl;
		cout << "\tAvec nomutilisateur qui est le nom du joueur dans le serveur (chaîne de caractères)" << endl;
		cout << "\tpseudo qui est le pseudonyme choisi par le joueur" << endl;
		cout << "\tImage?, un chiffre qui indique s'il y a une image (1) ou non (0)" << endl;
		cout << "\tet n1 à n8 qui est la stratégie du joueur (chiffres)" << endl;
		cout << "\nSi vous avez des problèmes avec la création du fichier HTML, regardez s'il y a un dossier 'swan' dans le répertoire où se trouve ce logiciel." << endl;
		cout << "Regardez aussi si les fichiers anon.png, logo.png, Quicksand.ttf, RussoOne.ttf et style.css sont dans le dossier swan." << endl;
		cout << "Réferrez-vous à la documentation pour plus d'informations." << endl;
		exit(1);
	}

	// read file
	string csv_filename = argv[1];

	ifstream csv(csv_filename);
	if(!csv.is_open())
	{
		cout << "Fichier CSV non trouvable. Veuillez vérifier ce que vous avez écrit." << endl;
		exit(1);
	}

	string line;
	while(getline(csv, line))
	{
		if(linenum == 0){
			if(countNumFields(line) == 2){
				vector<string> split_line = lineSplitter(line, ",");
				try {
					for(string a: lineSplitter(split_line[2], "|"))
						point_scheme.push_back(stoi(a));
					season = stoi(split_line[0]);
					season_slogan = split_line[1];
				} catch(invalid_argument &e) {
					//erreur 1
					cout << "La première ligne contient des valeurs invalides. Veuillez vérifier le fichier que vous avez mis." << endl;
					exit(1);
				}
			} else {
				//erreur 2
				cout << "La première ligne contient un nombre incorrecte de champs. Veuillez vérifier le fichier que vous avez mis." << endl;
				exit(1);
			}
        } else if(countNumFields(line) == 3) users.push_back(User(lineSplitter(line, ","), point_scheme));
		else {
			//erreur 3
			cout << "Erreur à la ligne " << linenum+1 << " du fichier. Nombre de champs incorrects." << endl;
			exit(1);
		}
		++linenum;
	}
	
	//erreur 4
	if(linenum == 0){
		cout << "Le fichier que vous avez donné est vide. Veuillez le vérifier." << endl;
		exit(1);
	}
	
	//erreur 5
	if(linenum < 3){
		cout << "Il n'y a pas assez de lignes dans votre fichier pour un classement. Veuillez le vérifier." << endl;
		exit(1);
	}
	
    // Affrontement des joueurs entre eux (de manière linéaire)
    play(users);
	
	// Tri fusion de la liste
	users = mergeSortVec(users);
	
	// Trouver l'utilisateur qui a le plus d'égalités
	mostDrawsFinder(users);

	// write file
	string html_filename = "swan/saison" + to_string(season) + ".html";

	ofstream html(html_filename);
	if(!html.is_open())
	{
		cout << "Erreur en ouvrant le fichier HTML. Veuillez vérifier qu'il n'est pas ouvert par un autre logiciel." << endl;
		exit(1);
	}
	html << "<!DOCTYPE html>" << endl;
	html << "<html lang='fr'>" << endl;
    html << "	<head>" << endl;
	html << "		<meta name='viewport' content='width=device-width, initial-scale=1'>" << endl;
	html << "		<title>Classement Saison " << season << " | " << season_slogan << "</title>" << endl;
	html << "		<meta charset='utf-8'>" << endl;
	html << "		<link rel='stylesheet' href='style.css'>" << endl;
	html << "	</head>" << endl;
	html << "	<body>" << endl;
	html << "		<header>" << endl;
	html << "			<div id='logosaison'>" << endl;
	html << "				<a href='index.html'><img alt='Logo Swan' id='logo' src='logo.png'><p id='numero'>" << season << "</p></a>" << endl;
	html << "			</div>" << endl;
	html << "			<nav>" << endl;
	html << "				<a href='https://cours.iut-orsay.fr/course/view.php?id=1197' target='_blank'>LE PROJET MOODLE</a>" << endl;
	html << "			</nav>" << endl;
	html << "		</header>" << endl;
	html << "		<section id='titreresultat'>" << endl;
	html << "			<h1>RESULTATS DE LA SAISON " << season << "</h1>" << endl;
	html << "			<h1>" << season_slogan << "</h1>" << endl;
	html << "		</section>" << endl;
	html << "		<div id='listeresultat'>" << endl;
	html << "			<div id='tableau'>" << endl;
	html << "				<table id='classement'>" << endl;
	html << "					<thead>" << endl;
	html << "						<tr>" << endl;
	html << "							<th>Classement</th>" << endl;
	html << "							<th>Distinction</th>" << endl;
	html << "							<th>Image</th>" << endl;
	html << "							<th>Joueur</th>" << endl;
	html << "							<th>Points</th>" << endl;
	html << "							<th>Victoires</th>" << endl;
	html << "							<th>Défaites</th>" << endl;
	html << "							<th>Egalites</th>" << endl;
	html << "							<th>Strategie</th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "							<th style='display:none'></th>" << endl;
	html << "						</tr>" << endl;
	html << "					</thead>" << endl;
	html << "					<tbody>" << endl;
	pageBuilder(html,users);
	html << "					</tbody>" << endl;
	html << "				</table>" << endl;
	html << "			</div>" << endl;
	html << "		</div>" << endl;
	html << "	</body>" << endl;
	html << "</html>" << endl;
}

