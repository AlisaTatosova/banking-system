#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QtSql>
#include "dbmanager.h"

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private:
    void set_placeholder_color(QLineEdit* lineEdit, const QString& text, const QColor& color);
    void inputing_field(const QString& text, QLineEdit* lineedit, const QString& message);
    void set_status_left(QLabel* label);
    void set_status_right(QLabel* label);
    void add_two_labels_in_one_line(QHBoxLayout* layout, QLabel* first, QLabel* second);
    void add_two_linedits_in_one_line(QHBoxLayout* layout, QLineEdit* first, QLineEdit* second);
    void set_lineedit_left(QLineEdit* lineedit);
    void set_lineedit_right(QLineEdit* lineedit);

private:
    bool is_valid_name(const QString& name);
    bool is_valid_last_name(const QString& last_name);
    bool is_valid_date_of_birth(const QString& dob);
    bool is_valid_phone(const QString& phone);
    bool is_valid_Email(const QString& email);
    bool is_valid_age(const QString& age);
    bool is_valid_username(const QString& username);
    bool is_valid_password(const QString& password);
    bool is_valid_password_repeat(const QString& password, const QString& repeated_password);
    void valid_field(QLabel* status, const QString& message);
    void not_valid_field(QLabel* status, const QString& message);

private:
    void validate_registration();
    void insert_data(const QStringList& data);

private:
    QWidget* widget;
    QVBoxLayout* group_box_layout;
    QVBoxLayout* layout;
    QHBoxLayout* password_status_layout;
    QHBoxLayout* password_layout;
    QHBoxLayout* phone_username_status_layout;
    QHBoxLayout* phone_username_layout;
    QHBoxLayout* mail_age_status_layout;
    QHBoxLayout* mail_age_layout;
    QHBoxLayout* name_surname_status_layout;
    QHBoxLayout* name_surname_layout;
    QLabel* registration;
    QLineEdit* name_edit;
    QLineEdit* surname_edit;
    QLineEdit* mail_edit;
    QLineEdit* age_edit;
    QLineEdit* password_edit;
    QLineEdit* username_edit;
    QLineEdit* phone_edit;
    QLineEdit* password_repeat_edit;
    QPushButton* registration_button;
    QLabel* logo_image;
    QLabel* name_status;
    QLabel* surname_status;
    QLabel* mail_status;
    QLabel* age_status;
    QLabel* phone_status;
    QLabel* username_status;
    QLabel* password_status;
    QLabel* password_repeat_status;


    QSqlDatabase& db;
};

#endif // REGISTRATION_H
