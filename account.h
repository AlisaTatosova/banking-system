#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtDebug>
#include <QTableWidget>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>


class Account : public QDialog {
    Q_OBJECT

private slots:
    void cards_button_cliked();
    void apply_for_card_button_cliked();
    void apply_button_is_cliked(const QString& card_type);
    void my_cards_button_cliked();

public:
    explicit Account(QWidget *parent = nullptr, const QString& name = "", const QString& surname = "", const QString& username = "");
    ~Account();
    void handle_account_operations();
    void create_logo_button(QHBoxLayout* hbox, QPushButton* button, QLabel* label, const QString& image_path);
    void add_logo_and_button_in_one_line(QHBoxLayout* layout, QLabel* logo, QPushButton* button);
    void set_logo();
    void cards_section_handler();
    void set_cards(QLabel* card_image, const QString& path);
    void add_to_group_box();
    void setting_pictures_for_echange();
    void add_to_bank_features();
    void hide_centeral_screen();



private:
    QString m_name;
    QString m_surname;
    QString m_username;
    QWidget* buttons_widget;
    QVBoxLayout* group_box_layout;
    QPushButton* profile_button;
    QPushButton* cards_button;
    QPushButton* transfer_button;
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
    QWidget* centeral_screen;
    QVBoxLayout* center;
    QWidget* features_widget;
    QHBoxLayout* layout;
    QVBoxLayout* bank_features;
    QLabel* about_us;
    QLabel* info;
    QLabel* exchange;
    QTableWidget* table_exchange;
    QLabel* name_surname_label;
    QLabel* usd_label;
    QLabel* eur_label;
    QLabel* uah_label;

    QPushButton* my_cards;
    QPushButton* apply_for_cards;
    QLabel* card_label;



    QLabel* business_card_image;
    QLabel* visa_card_image;
    QLabel* business_card;
    QLabel* visa_card;
    QPushButton* apply_business_card;
    QPushButton* apply_visa_card;

    long long random;
    QLabel* my_cards_business_card;
    QLabel* my_card_visa_card_image;
    QLabel* my_card_business_card_image;


};

#endif // ACCOUNT_H
