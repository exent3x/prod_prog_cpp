#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_map>
#include "User.h"
#include "Group.h"

class UserManager {
public:
    std::string createUser(const std::string& userId, const std::string& username, const std::string& extraInfo = "");
    std::string deleteUser(const std::string& userId);
    std::string allUsers() const;
    std::string getUser(const std::string& userId) const;
    
    std::string createGroup(const std::string& groupId);
    std::string deleteGroup(const std::string& groupId);
    std::string allGroups() const;
    std::string getGroup(const std::string& groupId) const;
    
    std::string addUserToGroup(const std::string& userId, const std::string& groupId);
    std::string removeUserFromGroup(const std::string& userId);
    
private:
    std::unordered_map<std::string, User> users_;
    std::unordered_map<std::string, Group> groups_;
};

#endif