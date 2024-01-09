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
    ~Login();

private slots:
    void authenticate();
    void inputing_field(const QString& text, QLineEdit* line_edit, const QString& message);
   // void inputing_password(const QString& text);
    void set_placeholder_color(QLineEdit* line_edit, const QString& text, const QColor& color);

    void show_password_click();
    void register_cliked();
    void forgett_password_button_cliked();

    QString retrieve_name(const QString& username);
    QString retrieve_surname(const QString& username);

private:
    void set_linedit(QLineEdit* line_edit, const QString& placeholder, bool is_password = false);
    QWidget* window;
    QVBoxLayout* group_box_layout;
    QHBoxLayout* password_layout;
    QHBoxLayout* remember_forgetpassword_layout;
    QVBoxLayout* layout;
    QLabel* sign_in;
    QLineEdit* username_edit;
    QLineEdit* password_edit;
    QPushButton* show_password_button;
    QPushButton* forgett_password_button;
    QPushButton* login_button;
    QPushButton* register_button;
    QLabel* login_status;
    QLabel* password_status;
    QLabel* logo_image;
    QCheckBox* remember_me_checkbox;

    QSqlDatabase& db;
};

#endif // LOGIN_H

