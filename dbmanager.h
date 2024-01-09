#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>

class DbManager {
public:
    static DbManager& instance();
    bool open_database();
    void close_database();
    QSqlDatabase& get_database();
    static void create_tables();
    static bool deposit(int account_id, double amount);
    static bool withdraw(int account_id, double amount);

private:
    DbManager();
    ~DbManager();

    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

    QSqlDatabase db;
};


#endif // DBMANAGER_H
