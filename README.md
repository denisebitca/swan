# **SWAN**

## **Remerciements**

Merci à Erika Carter du Noun Project pour [l'icône Swan](swan/logo.png).
Ce logiciel a été crée dans le cadre du projet tutoré du premier semestre à l'IUT d'Orsay.

La redistribution de ce logiciel dans toutes ses formes est autorisée uniquement avec l'accord de [Benjamin BREHIER--CARDOSO](https://benjaminbrehier.fr), [Clément GERAUDIE](https://clementgeraudie.fr) et Denise BITCA.

## *Repartition du travail*  

### *C++* : Benjamin BREHIER--CARDOSO et Denise BITCA

- 16/12/2020 : Programmation du code de lecture des stratégies et d'attribution des points
- 20/12/2020 : Programmation du tri fusion et début de l'assemblage du C++ et du HTML
- 27/12/2020 : Fin de la programmation des distinctions, des tests et début de la documentation

### *HTML - CSS* : Clément GERAUDIE

- 16/12/2020 : Commencement des maquettes pour le design
- 18/12/2020 : Création du design en HTML et CSS
- 19/12/2020 : Amélioration et optimisation du design sur PC
- 26/12/2020 : Adaptation du design au mobile

## **Outils collaboratifs**

Nous avons utilisé *Discord* ainsi que *Visual Studio Code Live Share* pour communiquer et partager les fichiers de notre logiciel.  

## **Programme**

### *Description*

Ce logiciel transforme un fichier CSV de strategies par plusieurs joueurs dans un fichier HTML qui classe ces joueurs *(réferrez-vous au document Swan pour les règles du jeu)*.

### *Utilisation*

Le logiciel, après avoir été compilé, doit être lancé à partir de la console de commandes, avec un argument ou une option.

#### *Commande*

> ``./strategy2html [FICHIER STRATEGIE CSV]``

Si la commande marche sans erreur, il n'y aura pas d'affichage. Un fichier HTML avec le nom ``saisonX.html`` (X étant un nombre) sera créé dans le répertoire ``swan``, qui doit être dans le même dossier que le logiciel.

#### *Options*

> ``./strategy2html --help``

> ``./strategy2html -h``

> ``./strategy2html``

Ces trois commandes retournent un affichage d'aide à l'utilisation du logiciel.

```
$> ./strategy2html --help
Usage: /home/toto/Desktop/strategy2html [FICHIER DE STRATEGIES SWAN CSV]

Options: -h (ou --help) (obtenir cet affichage)

Ce logiciel transforme un fichier de strategies de plusieurs joueurs dans un fichier HTML qui classe ces joueurs.

La première ligne du fichier de stratégies doit être dans ce format.
n1|n2|n3|n4|n5|n6|n7|n8,numSaison,devise_de_la_saison
        Avec n1 à n8 qui veut dire le nombre de points par tâche (chiffres)
        numSaison qui est le nombre de la saison Swan (chiffre)
        devise_de_la_saison qui est une chaîne de caractères

Les lignes qui suivent doivent être dans ce format :
nomutilisateur,pseudo,Image?,n1|n2|n3|n4|n5|n6|n7|n8
        Avec nomutilisateur qui est le nom du joueur dans le serveur (chaîne de caractères)
        pseudo qui est le pseudonyme choisi par le joueur
        Image?, un chiffre qui indique s'il y a une image (1) ou non (0)
        et n1 à n8 qui est la stratégie du joueur (chiffres)

Si vous avez des problèmes avec la création du fichier HTML, regardez s'il y a un dossier 'swan' dans le répertoire où se trouve ce logiciel.
Regardez aussi si les fichiers anon.png, logo.png, Quicksand.ttf, RussoOne.ttf et style.css sont dans le dossier swan.
Réferrez-vous à la documentation pour plus d'informations.
```

### *Erreurs*

>``Fichier CSV non trouvable. Veuillez vérifier ce que vous avez écrit.``

- Cela veut dire que le fichier CSV que vous avez indiqué n'existe pas dans le chemin que vous avez précisé. Vérifiez l'emplacement du fichier que vous cherchez.  

&nbsp;

>``La première ligne contient des valeurs invalides. Veuillez vérifier le fichier que vous avez mis.``

- Votre fichier CSV contient une valeur invalide dans un des champs de la première ligne. Voici un exemple d'une première ligne bien formattée : ``1,du côté de chez Swan,1|1|1|1|1|1|1|1``. Si le premier champ (délimité par une virgule) n'est pas un nombre, ou le dernier champ ne contient pas de nombres entre les "|", le logiciel vous donnera ce message d'erreur.

  - Essayez ``./strategy2html tests/test1-erreur1.csv`` pour tester cette erreur.

&nbsp;

>``La première ligne contient un nombre incorrecte de champs. Veuillez vérifier le fichier que vous avez mis.``

- Votre fichier CSV contient un nombre de champs incorrecte dans la première ligne. Cette ligne doit avoir deux champs. Voici un exemple d'une première ligne bien formattée : ``1,du côté de chez Swan,1|1|1|1|1|1|1|1``.

  - Essayez ``./strategy2html tests/test1-erreur2.csv`` pour tester cette erreur.

&nbsp;

>``Erreur à la ligne x du fichier. Nombre de champs incorrects.``

- Votre fichier CSV contient un nombre de champs incorrecte après la première ligne. Cette ligne doit avoir trois champs. Voici un exemple d'une ligne après la première ligne bien formattée : ``denise.bitca,toto,1,8|9|8|7|8|9|7|8``

  - Essayez ``./strategy2html tests/test1-erreur3.csv`` pour tester cette erreur.

&nbsp;

>``Le fichier que vous avez donné est vide. Veuillez le vérifier.``

- Votre fichier CSV est vide. Vérifiez le fichier.

  - Essayez ``./strategy2html tests/test1-erreur4.csv`` pour tester cette erreur.

&nbsp;

>``Il n'y a pas assez de lignes dans votre fichier pour un classement. Veuillez le vérifier.``
- Vous avez moins de deux stratégies différentes dans votre fichier CSV.

  - Essayez ``./strategy2html tests/test1-erreur5.csv`` pour tester cette erreur.
