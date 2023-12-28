#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>

class DbManager {
public:
    static DbManager& instance();
    bool open_database();
    void close_database();
    QSqlDatabase& get_database();

private:
    DbManager();
    ~DbManager();

    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

    QSqlDatabase db;
};



#endif // DBMANAGER_H
