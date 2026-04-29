#include "User.h"
#include "Group.h"
#include <sstream>

User::User(const std::string& userId, const std::string& username, const std::string& extraInfo)
    : user_id_(userId), username_(username), extra_info_(extraInfo), group_(nullptr) {}

const std::string& User::getUserId() const { return user_id_; }
const std::string& User::getUsername() const { return username_; }
const std::string& User::getExtraInfo() const { return extra_info_; }
Group* User::getGroup() const { return group_; }

void User::setGroup(Group* group) { group_ = group; }

std::string User::toString() const {
    std::ostringstream oss;
    oss << "ID: " << user_id_ << ", Имя: " << username_
        << ", Группа: " << (group_ ? group_->getGroupId() : "не состоит")
        << ", Доп. инфо: " << extra_info_;
    return oss.str();
}