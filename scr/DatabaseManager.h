#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <mysql/mysql.h>
#include <string>
#include <vector>

class DatabaseManager {
private:
    MYSQL *connection;

public:
    DatabaseManager(const std::string &host, const std::string &user,
                    const std::string &password, const std::string &dbName);
    ~DatabaseManager();

    bool connect();
    void addContact(const std::string &name, const std::vector<std::string> &phones,
                    const std::vector<std::string> &emails);
    std::vector<std::string> searchContact(const std::string &query);
    void listContacts();
};

#endif