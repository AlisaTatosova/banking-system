#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtDebug>


class Account : public QDialog {
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr, const QString& name = "", const QString& surname = "", const QString& username = "");
    ~Account();
    void handle_account_operations();
    void create_logo_button(QFrame* container, QHBoxLayout*& layout, QPushButton*& button, QLabel*& label, const QString& text, const QString& image_path);
    void add_logo_and_button_in_one_line(QHBoxLayout* layout, QLabel* logo, QPushButton* button);

private:
    QString m_name;
    QString m_surname;
    QString m_username;
    QWidget* buttons_widget;
    QVBoxLayout* group_box_layout;
    QPushButton* profile_button;
    QPushButton* cards_button;
    QPushButton* transfer_button;
    QPushButton* bill_button;
    QPushButton* logout_button;
    QLabel* logo_image;
    QHBoxLayout* profile;
    QFrame* profile_container;
    QLabel* profile_label;
    QHBoxLayout* cards;
    QLabel* cards_label;
    QFrame* cards_container;
    QHBoxLayout* transactions;
    QLabel* transactions_label;
    QFrame* transactions_container;
    QHBoxLayout* logout;
    QLabel* logout_label;
    QFrame* logout_container;
    QWidget* features_widget;
    QHBoxLayout* layout;
    QVBoxLayout* bank_features;

};

#endif // ACCOUNT_H
