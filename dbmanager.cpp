#include "dbmanager.h"
#include <QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <QSqlError>

DbManager::DbManager() {
    db = QSqlDatabase::addDatabase("QSQLITE"); // // adding db
    db.setDatabaseName("C:/Users/Admin/databases/my_db.db"); // setting db name
    if (!db.open()) {
        qDebug() << "Error: Couldn't open database. Reason:" << db.lastError().text();
    }
    create_tables();
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
    }

    return true;
}

void DbManager::close_database() {
    if (db.isOpen()) {
        db.close();
    }
}

QSqlDatabase& DbManager::get_database() {
    return db;
}

void DbManager::create_tables() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS clients ("
               "client_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT NOT NULL,"
               "surname TEXT NOT NULL,"
               "mail TEXT NOT NULL,"
               "age INTEGER NOT NULL,"
               "phone TEXT NOT NULL,"
               "username TEXT UNIQUE NOT NULL,"
               "password TEXT NOT NULL)");

    query.exec("CREATE TABLE IF NOT EXISTS bank_accounts ("
                "account_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "client_id INTEGER,"
                "account_number TEXT UNIQUE NOT NULL,"
                "balance REAL DEFAULT 0,"
                "FOREIGN KEY (client_id) REFERENCES clients(client_id))");

//            query.exec("CREATE TABLE IF NOT EXISTS bank_cards ("
//                       "card_id INTEGER PRIMARY KEY AUTOINCREMENT,"
//                       "client_id INTEGER,"
//                       "card_number TEXT UNIQUE NOT NULL,"
//                       "expiration_date DATE,"
//                       "cvv TEXT,"
//                       "FOREIGN KEY (client_id) REFERENCES clients(client_id))");

    query.exec("CREATE TABLE IF NOT EXISTS transactions ("
               "transaction_id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "account_id INTEGER,"
               "amount REAL,"
               "description TEXT,"
               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
               "FOREIGN KEY (account_id) REFERENCES bank_accounts(account_id))");
}




