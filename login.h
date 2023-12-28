#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QIcon>
#include <QtSql>
#include "registration.h"
#include "dbmanager.h"


class Login : public QWidget {
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);

private slots:
    void inputing_username(const QString& text);
    void inputing_password(const QString& text);
    void set_placeholder_color(QLineEdit* lineEdit, const QString& text, const QColor& color);
    void show_password_click();
    void register_cliked();
    void forgett_password_button_cliked();

    void authenticate();

private:
    QGroupBox* group_box;
    QLabel* username_label;
    QLineEdit* usernane_edit;
    QLabel* password_label;
    QLineEdit* password_edit;
    QPushButton* login_button;
    QLabel* sign_in;
    QLabel* logo_image;
    QCheckBox* remember_me_checkbox;
    QPushButton* show_password_button;
    QPushButton* register_button;
    QLabel* login_status;
    QLabel* password_status;
    QPushButton* forgett_password_button;

    QSqlDatabase& db;


};

#endif // LOGIN_H

