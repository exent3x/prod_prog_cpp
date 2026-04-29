#ifndef USER_H
#define USER_H

#include <string>

class Group;

class User {
public:
    User(const std::string& userId, const std::string& username, const std::string& extraInfo = "");
    
    const std::string& getUserId() const;
    const std::string& getUsername() const;
    const std::string& getExtraInfo() const;
    Group* getGroup() const;
    
    void setGroup(Group* group);
    
    std::string toString() const;
    
private:
    std::string user_id_;
    std::string username_;
    std::string extra_info_;
    Group* group_;
};

#endif