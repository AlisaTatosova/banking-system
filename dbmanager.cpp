#include "dbmanager.h"

DbManager::DbManager() {
    db = QSqlDatabase::addDatabase("QSQLITE"); // // adding db
    db.setDatabaseName("C:/Users/Admin/databases/my_db.db"); // setting db name
}

DbManager::~DbManager() {
    close_database(); // closing db
}

DbManager& DbManager::instance() {
    static DbManager instance;
    return instance;
}

bool DbManager::open_database() {
    // checking for connection
    if (!db.open()) {
        return false;
    } else {
        return true;
    }
}

void DbManager::close_database() {
    if (db.isOpen()) {
        db.close();
    }
}

QSqlDatabase& DbManager::get_database() {
    return db;
}
