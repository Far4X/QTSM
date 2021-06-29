#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <string>
#include <map>

const char *getHomeDir();
const std::string getListPath();
const std::string getDisclaimerMessage();
std::map<std::string, std::string> getDictFic();
void rewriteFile(const std::map<std::string, std::string> &dict);

#endif // COMMONFUNCTIONS_H
