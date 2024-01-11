#include "account.h"
#include <QApplication>
#include <QDesktopWidget>

Account::Account(QWidget *parent, const QString& name, const QString& surname, const QString& username)
    : QDialog(parent), m_name(name), m_surname(surname), m_username(username) {
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    QRect screen = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(screen);
    this -> setStyleSheet("background-color: black;");

    buttons_widget = new QWidget;
    buttons_widget -> setFixedSize(450, screen.height());
    buttons_widget -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5); border-radius: 15px;");

    group_box_layout = new QVBoxLayout(buttons_widget);
    group_box_layout -> setSpacing(0); //vertical spacing between widgets
    group_box_layout -> setAlignment(Qt::AlignTop);

    // using container to make same border for logo and button
    profile_container = new QFrame;
    create_logo_button(profile_container, profile, profile_button, profile_label, " Profile                      >  ", ":/images/profile.png");

    cards_container = new QFrame;
    create_logo_button(cards_container,cards, cards_button, cards_label, "Cards                       >  ", ":/images/cards.png");

    transactions_container = new QFrame;
    create_logo_button(transactions_container, transactions, transfer_button, transactions_label, "Transactions             >  ", ":/images/transfer.png");

    logout_container = new QFrame;
    create_logo_button(logout_container, logout, logout_button, logout_label, "Log out                    >  ", ":/images/logout.png");

    bill_button = new QPushButton("Bill                            >  ");
    bill_button -> setStyleSheet("border: none; border-bottom: 1px solid rgba(169, 169, 169, 0.5); font-size: 30px; color: white; text-align: left; padding-left: 30px;");

    QPixmap image(":/images/logo2.png");
    QPixmap scaled_pixmap = image.scaled(150, 150);
    if (scaled_pixmap.isNull()) {
        qDebug() << "Error loading image!";
    } else {
        logo_image = new QLabel(this);
        logo_image -> setPixmap(scaled_pixmap);
        logo_image -> setStyleSheet("border: none;");
        logo_image -> setAlignment(Qt::AlignCenter);
    }

    group_box_layout -> addWidget(logo_image);
    group_box_layout -> addSpacing(80);
    group_box_layout -> addWidget(profile_container);
    group_box_layout -> addSpacing(40);
    group_box_layout -> addWidget(cards_container);
    group_box_layout -> addSpacing(40);
    group_box_layout -> addWidget(transactions_container);
    group_box_layout -> addSpacing(40);
    group_box_layout -> addWidget(bill_button);
    group_box_layout -> addSpacing(40);
    group_box_layout -> addWidget(logout_container);
    group_box_layout -> addSpacing(40);


    features_widget = new QWidget;
    features_widget -> setFixedSize(450, screen.height());
    features_widget -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5); border-radius: 15px; ");
    bank_features = new QVBoxLayout(features_widget);
    bank_features -> setSpacing(0); //vertical spacing between widgets
    bank_features -> setAlignment(Qt::AlignTop);

    about_us = new QLabel("About us");
    about_us -> setStyleSheet("border: none;  border-bottom: 1px solid rgba(169, 169, 169, 0.5); color: white; font-size: 40px;  ");
    about_us -> setAlignment(Qt::AlignCenter);

    QString sentence = " The bank is known for its user-friendly\n online banking platform, allowing\n customers to conveniently manage \n their accounts and conduct transactions \n from the comfort of their homes";
    info = new QLabel(sentence);
    info -> setStyleSheet("margin-left: 30px; border: none; color: white; font-size: 20px;  ");

    exchange = new QLabel("Exchange");
    exchange -> setStyleSheet("border: none;  border-bottom: 1px solid rgba(169, 169, 169, 0.5); color: white; font-size: 38px;  ");
    exchange -> setAlignment(Qt::AlignCenter);

    table_exchange = new QTableWidget();
    table_exchange -> setRowCount(4);
    table_exchange -> setColumnCount(4);

    QStringList currencies = {"Currency", "1 USD", "1 EUR", "1 UAH"};
    QStringList buys = {"Buy", "410", "418", "8"};
    QStringList sells = {"Sell", "412", "420", "9.5"};

    for (int row = 0; row < currencies.size(); ++row) {
        table_exchange -> setItem(row, 1, new QTableWidgetItem(currencies[row]));
        table_exchange -> setItem(row, 2, new QTableWidgetItem(buys[row]));
        table_exchange -> setItem(row, 3, new QTableWidgetItem(sells[row]));
    }

    QPixmap usd(":/images/USD.png");
    usd_label = new QLabel();
    usd_label -> setPixmap(usd.scaled(45, 25));
    usd_label -> setStyleSheet("margin-left: 20px; border: none; ");
    table_exchange -> setCellWidget(1, 0, usd_label);

    QPixmap eur(":/images/EUR.png");
    eur_label = new QLabel();
    eur_label -> setPixmap(eur.scaled(45, 25));
    eur_label -> setStyleSheet("margin-left: 20px; border: none; ");
    table_exchange -> setCellWidget(2, 0, eur_label);

    QPixmap uah(":/images/UAH.png");
    uah_label = new QLabel();
    uah_label -> setPixmap(uah.scaled(45, 25));
    uah_label -> setStyleSheet("margin-left: 20px; border: none; ");
    table_exchange -> setCellWidget(3, 0, uah_label);

    table_exchange -> setStyleSheet("color: white; font-size: 22px; border: none");
    table_exchange -> setColumnWidth(0, 80); // to make 0r column less wider

    table_exchange -> verticalHeader() -> setVisible(false);
    table_exchange -> horizontalHeader() -> setVisible(false);


    bank_features -> addSpacing(20);
    bank_features -> addWidget(about_us);
    bank_features -> addSpacing(30);
    bank_features -> addWidget(info);
    bank_features -> addSpacing(35);
    bank_features -> addWidget(exchange);
    bank_features -> addSpacing(30);
    bank_features -> addWidget(table_exchange);
    bank_features -> addSpacing(30);


    centeral_screen = new QWidget;
    centeral_screen -> setFixedSize(screen.width() - features_widget -> width() - buttons_widget -> width() - 40, screen.height());
    centeral_screen -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5); border-radius: 15px; ");
    center = new QVBoxLayout(centeral_screen);
    center -> setSpacing(0); //vertical spacing between widgets
    center -> setAlignment(Qt::AlignTop);
    center -> addSpacing(25);


    name_surname_label = new QLabel(m_name.toUpper() + " " + m_surname.toUpper());
    name_surname_label -> setStyleSheet("border: none;  border-bottom: 1px solid rgba(169, 169, 169, 0.5); color: white; font-size: 50px;  ");
    name_surname_label -> setAlignment(Qt::AlignCenter);
    center -> addWidget(name_surname_label);


    layout = new QHBoxLayout(this);
    layout -> addWidget(buttons_widget,  0, Qt::AlignTop | Qt::AlignLeft);
    layout -> addWidget(centeral_screen, 0, Qt::AlignTop | Qt::AlignCenter);
    layout -> addWidget(features_widget,  0, Qt::AlignTop | Qt::AlignRight);

}

void Account::create_logo_button(QFrame* container, QHBoxLayout*& layout, QPushButton*& button, QLabel*& label, const QString& text, const QString& image_path) {
    container -> setStyleSheet("border: none; border-bottom: 1px solid rgba(169, 169, 169, 0.5); ");

    button = new QPushButton(text);
    button -> setStyleSheet("border: none; font-size: 30px; color: white; text-align: left; padding-left: 30px;");


    layout = new QHBoxLayout(container);
    QPixmap image(image_path);
    if (image.isNull()) {
        qDebug() << "Error loading image!";
    } else {
        label = new QLabel();
        if (image_path == ":/images/cards.png" ) {
            label -> setPixmap(image.scaled(50, 35));
            label -> setStyleSheet("border: none; padding-left: 10px;");
        } else if (image_path == ":/images/transfer.png") {
            label -> setPixmap(image.scaled(41, 40));
            label -> setStyleSheet("border: none; padding-left: 15px;");
        } else  if (image_path == ":/images/profile.png"){
            label -> setPixmap(image);
            label -> setStyleSheet("border: none; padding-left: 10px;");
        } else  if (image_path == ":/images/logout.png"){
            label -> setPixmap(image.scaled(38, 38));
            label -> setStyleSheet("border: none; padding-left: 18px;");
        }
    }
    // adding in one line logo and push button
    add_logo_and_button_in_one_line(layout, label, button);
}

void Account::add_logo_and_button_in_one_line(QHBoxLayout* layout, QLabel* logo, QPushButton* button) {
    layout -> addWidget(logo);
    layout -> addStretch();
    layout -> addWidget(button);
}

Account::~Account() {
    delete profile_button;
    delete cards_button;
    delete transfer_button;
    delete bill_button;
    delete logout_button;
    delete logo_image;
    delete profile_label;
    delete cards_label;
    delete transactions_label;
    delete logout_label;
    delete profile;
    delete cards;
    delete transactions;
    delete logout;
    delete profile_container;
    delete cards_container;
    delete transactions_container;
    delete logout_container;
    delete about_us;
    delete info;
    delete name_surname_label;
    delete group_box_layout;
    delete center;
    delete bank_features;
    delete layout;
    delete buttons_widget;
    delete centeral_screen;
    delete features_widget;

}
