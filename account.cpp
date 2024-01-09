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
    buttons_widget -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5);  border-bottom: none;  border-top: none; border-radius: 15px;");

    group_box_layout = new QVBoxLayout(buttons_widget);
    group_box_layout -> setSpacing(0); //vertical spacing between widgets
    group_box_layout -> setAlignment(Qt::AlignTop);

    // using container to make same border for logo and button
    profile_container = new QFrame;
    create_logo_button(profile_container, profile, profile_button, profile_label, " Profile                      >  ", ":/images/profile.png");

    // Usage for cards
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
    features_widget -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5);  border-bottom: none; border-top: none; border-radius: 15px; ");
    bank_features = new QVBoxLayout(features_widget);
    bank_features -> setSpacing(0); //vertical spacing between widgets
    bank_features -> setAlignment(Qt::AlignTop);


    layout = new QHBoxLayout(this);
    layout -> addWidget(buttons_widget,  0, Qt::AlignTop | Qt::AlignLeft);
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
    delete group_box_layout;
    delete bank_features;
    delete layout;
    delete buttons_widget;
    delete features_widget;

}
