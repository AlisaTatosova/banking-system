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
    create_table("Clients", QStringList() << "Name" << "Surname" << "Email" << "Age" << "Phone" << "Username" << "Password");
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

void DbManager::create_table(const QString& table_name, const QStringList& column_names) {
    QSqlQuery query;
    QString table = "CREATE TABLE " + table_name + " (";
    for (const QString& col : column_names) {
        table += col + " VARCHAR(255), ";
    }
    table.chop(2); // removing the trailing comma and space
    table += ")";
    query.exec(table);
}
