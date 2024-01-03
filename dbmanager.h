#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>

class DbManager {
public:
    static DbManager& instance();
    bool open_database();
    void close_database();
    QSqlDatabase& get_database();
    void create_table(const QString& tableName, const QStringList& column_names);

private:
    DbManager();
    ~DbManager();

    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

    QSqlDatabase db;
};


#endif // DBMANAGER_H
