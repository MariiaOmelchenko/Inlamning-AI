#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string &host, const std::string &user,
                                 const std::string &password, const std::string &dbName) {
    connection = mysql_init(nullptr);
    if (!connection) {
        std::cerr << "MySQL initialization failed." << std::endl;
    }

    if (!mysql_real_connect(connection, host.c_str(), user.c_str(), password.c_str(),
                            dbName.c_str(), 0, nullptr, 0)) {
        std::cerr << "Connection failed: " << mysql_error(connection) << std::endl;
        connection = nullptr;
    }
}

DatabaseManager::~DatabaseManager() {
    if (connection) {
        mysql_close(connection);
    }
}

bool DatabaseManager::connect() {
    return connection != nullptr;
}

void DatabaseManager::addContact(const std::string &name,
                                  const std::vector<std::string> &phones,
                                  const std::vector<std::string> &emails) {
    std::string query = "INSERT INTO Contacts (name) VALUES ('" + name + "')";
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Failed to add contact: " << mysql_error(connection) << std::endl;
        return;
    }

    int contactId = mysql_insert_id(connection);

    for (const auto &phone : phones) {
        query = "INSERT INTO ContactDetails (contact_id, type, value) VALUES (" +
                std::to_string(contactId) + ", 'phone', '" + phone + "')";
        if (mysql_query(connection, query.c_str())) {
            std::cerr << "Failed to add phone: " << mysql_error(connection) << std::endl;
        }
    }

    for (const auto &email : emails) {
        query = "INSERT INTO ContactDetails (contact_id, type, value) VALUES (" +
                std::to_string(contactId) + ", 'email', '" + email + "')";
        if (mysql_query(connection, query.c_str())) {
            std::cerr << "Failed to add email: " << mysql_error(connection) << std::endl;
        }
    }
}

void DatabaseManager::listContacts() {
    const char *query = "SELECT Contacts.id, Contacts.name, ContactDetails.type, ContactDetails.value "
                        "FROM Contacts LEFT JOIN ContactDetails ON Contacts.id = ContactDetails.contact_id";
    if (mysql_query(connection, query)) {
        std::cerr << "Failed to fetch contacts: " << mysql_error(connection) << std::endl;
        return;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (!result) {
        std::cerr << "Failed to store result: " << mysql_error(connection) << std::endl;
        return;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        std::cout << "ID: " << row[0] << ", Name: " << row[1]
                  << ", Type: " << row[2] << ", Value: " << row[3] << std::endl;
    }

    mysql_free_result(result);
}
