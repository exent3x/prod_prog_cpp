#include "UserManager.h"
#include <sstream>

std::string UserManager::createUser(const std::string& userId, const std::string& username, const std::string& extraInfo) {
    if (users_.find(userId) != users_.end())
        return "Ошибка: пользователь с ID '" + userId + "' уже существует.";
    if (username.empty())
        return "Ошибка: имя пользователя не может быть пустым.";
    
    users_.emplace(userId, User(userId, username, extraInfo));
    return "Пользователь '" + username + "' (ID: " + userId + ") успешно создан.";
}

std::string UserManager::deleteUser(const std::string& userId) {
    auto it = users_.find(userId);
    if (it == users_.end())
        return "Ошибка: пользователь с ID '" + userId + "' не найден.";
    
    User& user = it->second;
    if (user.getGroup()) {
        user.getGroup()->removeUser(&user);
        user.setGroup(nullptr);
    }
    users_.erase(it);
    return "Пользователь с ID '" + userId + "' удалён.";
}

std::string UserManager::allUsers() const {
    if (users_.empty())
        return "Список пользователей пуст.";
    
    std::ostringstream oss;
    oss << "Список всех пользователей:\n";
    for (const auto& pair : users_) {
        oss << "  " << pair.second.toString() << "\n";
    }
    return oss.str();
}

std::string UserManager::getUser(const std::string& userId) const {
    auto it = users_.find(userId);
    if (it == users_.end())
        return "Ошибка: пользователь с ID '" + userId + "' не найден.";
    return it->second.toString();
}

std::string UserManager::createGroup(const std::string& groupId) {
    if (groups_.find(groupId) != groups_.end())
        return "Ошибка: группа с ID '" + groupId + "' уже существует.";
    
    groups_.emplace(groupId, Group(groupId));
    return "Группа с ID '" + groupId + "' успешно создана.";
}

std::string UserManager::deleteGroup(const std::string& groupId) {
    auto it = groups_.find(groupId);
    if (it == groups_.end())
        return "Ошибка: группа с ID '" + groupId + "' не найдена.";
    
    Group& group = it->second;
    for (User* user : group.getUsers()) {
        if (user) user->setGroup(nullptr);
    }
    groups_.erase(it);
    return "Группа с ID '" + groupId + "' удалена.";
}

std::string UserManager::allGroups() const {
    if (groups_.empty())
        return "Список групп пуст.";
    
    std::ostringstream oss;
    oss << "Список всех групп:\n";
    for (const auto& pair : groups_) {
        oss << "  " << pair.second.toString() << "\n";
    }
    return oss.str();
}

std::string UserManager::getGroup(const std::string& groupId) const {
    auto it = groups_.find(groupId);
    if (it == groups_.end())
        return "Ошибка: группа с ID '" + groupId + "' не найдена.";
    return it->second.toString();
}

std::string UserManager::addUserToGroup(const std::string& userId, const std::string& groupId) {
    auto userIt = users_.find(userId);
    if (userIt == users_.end())
        return "Ошибка: пользователь с ID '" + userId + "' не найден.";
    
    auto groupIt = groups_.find(groupId);
    if (groupIt == groups_.end())
        return "Ошибка: группа с ID '" + groupId + "' не найдена.";
    
    User* user = &userIt->second;
    Group* newGroup = &groupIt->second;
    
    if (user->getGroup() == newGroup)
        return "Пользователь уже состоит в этой группе.";
    
    if (user->getGroup()) {
        user->getGroup()->removeUser(user);
    }
    
    newGroup->addUser(user);
    user->setGroup(newGroup);
    return "Пользователь '" + user->getUsername() + "' добавлен в группу '" + groupId + "'.";
}

std::string UserManager::removeUserFromGroup(const std::string& userId) {
    auto userIt = users_.find(userId);
    if (userIt == users_.end())
        return "Ошибка: пользователь с ID '" + userId + "' не найден.";
    
    User* user = &userIt->second;
    if (!user->getGroup())
        return "Пользователь не состоит ни в какой группе.";
    
    Group* oldGroup = user->getGroup();
    oldGroup->removeUser(user);
    user->setGroup(nullptr);
    return "Пользователь '" + user->getUsername() + "' удалён из группы '" + oldGroup->getGroupId() + "'.";
}