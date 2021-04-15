#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

class User {
    private:
        std::string un;
        std::string pn;
        std::string img;
        std::string strategy;
        std::vector<int> pointscheme;
        int wins = 0;
        int draws = 0;
        int loss = 0;
		bool hmd = false;
    public:

        // getters
        std::vector<int> strat() const; 
		std::string strat_string() const;
        std::string username() const;
        std::string pseudonym() const;
        bool hasImage() const;
        int getWin() const;
        int getDraws() const;
        int getPoints() const;
        int getLoss() const;
		bool hasMostDraws() const;

        // setters
        void addWin();
        void addDraw();
        void addLoss();
		void setMostDrawstoTrue();

        // autres fonctions membre
        void pointCounter(User &u2);

        // operator
		bool operator>(const User &u2);

        User(std::vector<std::string>, std::vector<int>&); // constructeur
};

std::ostream& operator<<(std::ostream &os, const User &u); // debougage


#endif // USER_H_INCLUDED
