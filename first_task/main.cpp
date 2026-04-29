#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cctype>
#include "UserManager.h"
#include <windows.h>
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

void printHelp() {
    std::cout << "Доступные команды:\n"
              << "  createUser <userId> <username> [доп. информация]\n"
              << "  deleteUser <userId>\n"
              << "  allUsers\n"
              << "  getUser <userId>\n"
              << "  createGroup <groupId>\n"
              << "  deleteGroup <groupId>\n"
              << "  allGroups\n"
              << "  getGroup <groupId>\n"
              << "  addUserToGroup <userId> <groupId>\n"
              << "  removeUserFromGroup <userId>\n"
              << "  help\n"
              << "  exit / quit\n";
}

void handleCreateUser(UserManager& m, std::istringstream& iss) {
    std::string userId, username, extra;
    iss >> userId >> username;
    std::getline(iss, extra);
    if (!extra.empty() && extra[0] == ' ') extra.erase(0, 1);
    if (userId.empty() || username.empty()) {
        std::cout << "Ошибка: необходимо указать userId и username." << std::endl;
        return;
    }
    std::cout << m.createUser(userId, username, extra) << std::endl;
}

void handleDeleteUser(UserManager& m, std::istringstream& iss) {
    std::string userId;
    iss >> userId;
    if (userId.empty()) {
        std::cout << "Ошибка: необходимо указать userId." << std::endl;
        return;
    }
    std::cout << m.deleteUser(userId) << std::endl;
}

void handleAllUsers(UserManager& m, std::istringstream&) {
    std::cout << m.allUsers() << std::endl;
}

void handleGetUser(UserManager& m, std::istringstream& iss) {
    std::string userId;
    iss >> userId;
    if (userId.empty()) {
        std::cout << "Ошибка: необходимо указать userId." << std::endl;
        return;
    }
    std::cout << m.getUser(userId) << std::endl;
}

void handleCreateGroup(UserManager& m, std::istringstream& iss) {
    std::string groupId;
    iss >> groupId;
    if (groupId.empty()) {
        std::cout << "Ошибка: необходимо указать groupId." << std::endl;
        return;
    }
    std::cout << m.createGroup(groupId) << std::endl;
}

void handleDeleteGroup(UserManager& m, std::istringstream& iss) {
    std::string groupId;
    iss >> groupId;
    if (groupId.empty()) {
        std::cout << "Ошибка: необходимо указать groupId." << std::endl;
        return;
    }
    std::cout << m.deleteGroup(groupId) << std::endl;
}

void handleAllGroups(UserManager& m, std::istringstream&) {
    std::cout << m.allGroups() << std::endl;
}

void handleGetGroup(UserManager& m, std::istringstream& iss) {
    std::string groupId;
    iss >> groupId;
    if (groupId.empty()) {
        std::cout << "Ошибка: необходимо указать groupId." << std::endl;
        return;
    }
    std::cout << m.getGroup(groupId) << std::endl;
}

void handleAddUserToGroup(UserManager& m, std::istringstream& iss) {
    std::string userId, groupId;
    iss >> userId >> groupId;
    if (userId.empty() || groupId.empty()) {
        std::cout << "Ошибка: необходимо указать userId и groupId." << std::endl;
        return;
    }
    std::cout << m.addUserToGroup(userId, groupId) << std::endl;
}

void handleRemoveUserFromGroup(UserManager& m, std::istringstream& iss) {
    std::string userId;
    iss >> userId;
    if (userId.empty()) {
        std::cout << "Ошибка: необходимо указать userId." << std::endl;
        return;
    }
    std::cout << m.removeUserFromGroup(userId) << std::endl;
}

void handleExit(UserManager&, std::istringstream&) {
    std::cout << "До свидания!" << std::endl;
    exit(0);
}

int main() {
    UserManager manager;
    std::cout << "Система управления пользователями и группами\n";
    printHelp();
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::unordered_map<std::string, std::function<void(UserManager&, std::istringstream&)>> commands = {
        {"help",      [](UserManager&, std::istringstream&) { printHelp(); }},
        {"exit",      handleExit},
        {"quit",      handleExit},
        {"createuser", handleCreateUser},
        {"deleteuser", handleDeleteUser},
        {"allusers",   handleAllUsers},
        {"getuser",    handleGetUser},
        {"creategroup", handleCreateGroup},
        {"deletegroup", handleDeleteGroup},
        {"allgroups",  handleAllGroups},
        {"getgroup",   handleGetGroup},
        {"addusertogroup", handleAddUserToGroup},
        {"removeuserfromgroup", handleRemoveUserFromGroup}
    };

    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (!std::cin) break;

        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        line = line.substr(start);

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        std::string lowerCmd = toLower(cmd);

        auto it = commands.find(lowerCmd);
        if (it != commands.end()) {
            it->second(manager, iss);
        } else if (!cmd.empty()) {
            std::cout << "Неизвестная команда. Введите 'help' для справки." << std::endl;
        }
    }
    return 0;
}