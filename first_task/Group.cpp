#include "Group.h"
#include "User.h"
#include <sstream>
#include <algorithm>

Group::Group(const std::string& groupId) : group_id_(groupId) {}

const std::string& Group::getGroupId() const { return group_id_; }
const std::vector<User*>& Group::getUsers() const { return users_; }

void Group::addUser(User* user) {
    if (user && std::find(users_.begin(), users_.end(), user) == users_.end()) {
        users_.push_back(user);
    }
}

void Group::removeUser(User* user) {
    auto it = std::find(users_.begin(), users_.end(), user);
    if (it != users_.end()) {
        users_.erase(it);
    }
}

std::string Group::toString() const {
    std::ostringstream oss;
    oss << "Группа ID: " << group_id_ << ", Пользователи: [";
    for (size_t i = 0; i < users_.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << users_[i]->getUsername();
    }
    oss << "]";
    return oss.str();
}