# ifndef _UTIL_H_
# define _UTIL_H_
# include<string>
# include<vector>

bool deteckWorkerIP(std::string ip);

std::vector<std::string> split(const std::string& value,int number);

std::string combine(std::vector<std::string>& values);


# endif
