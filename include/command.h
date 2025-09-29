#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
//3
//reads text command and splits them into tokens

//Example SET name John
//Command = Set, key = name, value = ben
class Command {
public:
    static std::vector<std::string> parse(const std::string& line);
};

#endif
