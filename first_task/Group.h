#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

class User;

class Group {
public:
    explicit Group(const std::string& groupId);
    
    const std::string& getGroupId() const;
    const std::vector<User*>& getUsers() const;
    
    void addUser(User* user);
    void removeUser(User* user);
    
    std::string toString() const;
    
private:
    std::string group_id_;
    std::vector<User*> users_;
};

#endif