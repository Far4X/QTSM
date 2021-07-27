#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <string>
#include <map>

const char *getHomeDir();
const std::string getListPath();
const std::string getDisclaimerMessage();
std::map<std::string, std::string> getDictFic();
void rewriteFile(const std::map<std::string, std::string> &dict);
void changeProjectNameAndRefresh(std::string old_project_name, std::string new_project_name);
void changeProjectPathAndRefresh(std::string project_name, std::string new_path);
void replaceWord(std::string &original, const std::string &to_find, const std::string &to_replace);

#endif // COMMONFUNCTIONS_H
