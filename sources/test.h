#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <string>
#include <vector>
#include "user.h"

int countNumFields(std::string&);
std::vector<std::string> lineSplitter(std::string, std::string);
void play(std::vector<User> &u);

void pageBuilder(std::ostream&, std::vector<User>&);

std::vector<User> mergeSortVec(const std::vector<User>&);
std::vector<User> merge(std::vector<User>&, std::vector<User>&);

void mostDrawsFinder(std::vector<User>&);

#endif // TEST_H_INCLUDED
