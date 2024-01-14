#include "account.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>

void Account::cards_button_cliked() {
    for (int i = 0; i < center -> count(); ++i) {
        QWidget* widget = center -> itemAt(i)-> widget();
        if (widget) {
            widget -> hide();
        }
    }

    center -> addSpacing(25);
    card_label -> setAlignment(Qt::AlignCenter);
    center -> addWidget(card_label);
    center -> addSpacing(250);
    center -> addWidget(my_cards, 0, Qt::AlignCenter);
    center -> addSpacing(50);
    center -> addWidget(apply_for_cards, 0, Qt::AlignCenter);
    center -> addSpacing(-325);
}

void Account::apply_for_card_button_cliked() {
    my_cards -> hide();
    apply_for_cards -> hide();

    business_card -> setStyleSheet("border: none; color: white; font-size: 38px;");
    visa_card -> setStyleSheet("border: none;  border-top: 1px solid rgba(169, 169, 169, 0.5); color: white; font-size: 38px;");
    apply_business_card -> setStyleSheet("border: 2px solid grey; border-radius: 15px; font-size: 25px; color: white;");
    apply_business_card -> setFixedSize(300, 45);
    apply_visa_card -> setStyleSheet("border: 2px solid grey; border-radius: 15px; font-size: 25px; color: white;");
    apply_visa_card -> setFixedSize(300, 45);


    center -> addSpacing(50);
    center -> addWidget(business_card);
    center -> addSpacing(20);
    set_cards(business_card_image, ":/images/business_card.JPG");
    center -> addSpacing(20);
    center -> addWidget(apply_business_card, 0, Qt::AlignCenter);
    center -> addSpacing(30);
    center -> addWidget(visa_card);
    center -> addSpacing(20);
    set_cards(visa_card_image, ":/images/visa_card.JPG");
    center -> addSpacing(30);
    center -> addWidget(apply_visa_card, 0, Qt::AlignCenter);

    center -> addSpacing(-150);
}

void Account::set_cards(QLabel* card_image, const QString& path) {
    QPixmap image(path);
    QPixmap scaled = image.scaled(400, 220);

    if (scaled.isNull()) {
        qDebug() << "Error loading image!";
    } else {
        QPainter painter(&scaled);

        QFont font;
        font.setPointSize(18);
        painter.setFont(font);

        painter.setPen(Qt::white); // text color
        painter.drawText(60, scaled.height() - 70, "**** **** **** ****"); // position of text
        painter.end(); // end the painting

        card_image -> setPixmap(scaled);
        card_image -> setStyleSheet("border: none;");
        card_image -> setAlignment(Qt::AlignCenter);

        center -> addWidget(card_image);
        //business_card_layout -> addWidget(card_image, 0, Qt::AlignTop);

    }
}

void Account::cards_section_handler() {
    card_label -> setStyleSheet("border: none; border-bottom: 1px solid rgba(169, 169, 169, 0.5); font-size: 40px; color: white;  ");
    my_cards -> setFixedSize(600, 60);
    my_cards -> setStyleSheet("border-radius: 15px; font-size: 30px; color: white; ");
    apply_for_cards -> setFixedSize(600, 60);
    apply_for_cards -> setStyleSheet("border-radius: 15px; font-size: 30px; color: white; ");
    connect(cards_button, &QPushButton::clicked, this, &Account::cards_button_cliked);
    connect(apply_for_cards, &QPushButton::clicked, this, &Account::apply_for_card_button_cliked);
}


Account::Account(QWidget *parent, const QString& name, const QString& surname, const QString& username)
    : QDialog(parent), m_name(name), m_surname(surname), m_username(username) {
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    QRect screen = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(screen);
    this -> setStyleSheet("background-color: black;");

    logo_image = new QLabel(this);
    set_logo();

    // handling the left part of screen
    buttons_widget = new QWidget;
    buttons_widget -> setFixedSize(450, screen.height());
    buttons_widget -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5); border-radius: 15px;");

    group_box_layout = new QVBoxLayout(buttons_widget);

    // using container to make same border for logo and button
    profile_container = new QFrame;
    profile_container -> setStyleSheet("border: none; border-bottom: 1px solid rgba(169, 169, 169, 0.5); ");
    profile_button = new QPushButton(" Profile                      > ");
    profile = new QHBoxLayout(profile_container);
    profile_label = new QLabel();

    create_logo_button(profile, profile_button, profile_label, ":/images/profile.png");

    // using container to make same border for card logo and button
    cards_container = new QFrame;
    cards_container -> setStyleSheet("border: none; border-bottom: 1px solid rgba(169, 169, 169, 0.5); ");
    cards_button = new QPushButton(" Cards                      > ");
    cards = new QHBoxLayout(cards_container);
    cards_label = new QLabel();
    create_logo_button(cards, cards_button, cards_label, ":/images/cards.png");

    business_card_image = new QLabel();
    visa_card_image = new QLabel();
    business_card = new QLabel("Business Card");
    business_card -> setAlignment(Qt::AlignHCenter);
    visa_card = new QLabel("Visa Card");
    visa_card -> setAlignment(Qt::AlignHCenter);
    apply_visa_card = new QPushButton("Apply");
    apply_business_card = new QPushButton("Apply");


    card_label = new QLabel("Cards");    
    my_cards = new QPushButton("My cards");
    apply_for_cards = new QPushButton("Apply for cards"); 
    cards_section_handler();


    // using container to make same border for transaction logo and button
    transactions_container = new QFrame;
    transactions_container -> setStyleSheet("border: none; border-bottom: 1px solid rgba(169, 169, 169, 0.5); ");
    transfer_button = new QPushButton(" Transactions                      > ");
    transactions = new QHBoxLayout(transactions_container);
    transactions_label = new QLabel();
    create_logo_button(transactions, transfer_button, transactions_label, ":/images/transfer.png");


    // using container to make same border for logout logo and button
    logout_container = new QFrame;
    logout_container -> setStyleSheet("border: none; border-bottom: 1px solid rgba(169, 169, 169, 0.5); ");
    logout_button = new QPushButton("Log out                    >  ");
    logout = new QHBoxLayout(logout_container);
    logout_label = new QLabel();
    create_logo_button(logout, logout_button, logout_label, ":/images/logout.png");

    // adding appropriate widgets to groupbox layout
    add_to_group_box();

    // handling the right part of screen
    features_widget = new QWidget;
    features_widget -> setFixedSize(450, screen.height());
    features_widget -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5); border-radius: 15px; ");

    bank_features = new QVBoxLayout(features_widget);

    about_us = new QLabel("About us");
    about_us -> setStyleSheet("border: none;  border-bottom: 1px solid rgba(169, 169, 169, 0.5); color: white; font-size: 40px;  ");
    about_us -> setAlignment(Qt::AlignCenter);

    QString sentence = " The bank is known for its user-friendly\n online banking platform, allowing\n customers to conveniently manage \n their accounts and conduct transactions \n from the comfort of their homes";
    info = new QLabel(sentence);
    info -> setStyleSheet("margin-left: 30px; border: none; color: white; font-size: 20px;  ");

    // exchange rate label
    exchange = new QLabel("Exchange");
    exchange -> setStyleSheet("border: none;  border-bottom: 1px solid rgba(169, 169, 169, 0.5); color: white; font-size: 38px;  ");
    exchange -> setAlignment(Qt::AlignCenter);

    // exchange rate table creation
    table_exchange = new QTableWidget;
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

    //setting pictures for exchange
    setting_pictures_for_echange();
    add_to_bank_features();

    // handling the centeral part of window
    centeral_screen = new QWidget;
    center = new QVBoxLayout(centeral_screen);
    centeral_screen -> setFixedSize(screen.width() - features_widget -> width() - buttons_widget -> width() - 40, screen.height());
    centeral_screen -> setStyleSheet(" border: 1px solid rgba(169, 169, 169, 0.5); border-radius: 15px; ");


    name_surname_label = new QLabel(m_name.toUpper() + " " + m_surname.toUpper());
    name_surname_label -> setStyleSheet("border: none;  border-bottom: 1px solid rgba(169, 169, 169, 0.5); color: white; font-size: 50px;  ");
    name_surname_label -> setAlignment(Qt::AlignCenter);

    center -> setSpacing(0); //vertical spacing between widgets
    center -> setAlignment(Qt::AlignTop);
    center -> addSpacing(25);
    center -> addWidget(name_surname_label);


    // adding all widgets to main layout
    layout = new QHBoxLayout(this);
    layout -> addWidget(buttons_widget,  0, Qt::AlignTop | Qt::AlignLeft);
    layout -> addWidget(centeral_screen, 0, Qt::AlignTop | Qt::AlignCenter);
    layout -> addWidget(features_widget,  0, Qt::AlignTop | Qt::AlignRight);

}


void Account::set_logo() {
    QPixmap image(":/images/logo2.png");
    QPixmap scaled_pixmap = image.scaled(150, 150);
    if (scaled_pixmap.isNull()) {
        qDebug() << "Error loading image!";
    } else {
        logo_image -> setPixmap(scaled_pixmap);
        logo_image -> setStyleSheet("border: none;");
        logo_image -> setAlignment(Qt::AlignCenter);
    }
}

void Account::add_to_group_box() {
    group_box_layout -> setSpacing(0); //vertical spacing between widgets
    group_box_layout -> setAlignment(Qt::AlignTop);
    group_box_layout -> addWidget(logo_image);
    group_box_layout -> addSpacing(80);
    group_box_layout -> addWidget(profile_container);
    group_box_layout -> addSpacing(40);
    group_box_layout -> addWidget(cards_container);
    group_box_layout -> addSpacing(40);
    group_box_layout -> addWidget(transactions_container);
    group_box_layout -> addSpacing(40);
    group_box_layout -> addWidget(logout_container);
    group_box_layout -> addSpacing(40);
}

void Account::add_to_bank_features() {
    bank_features -> setSpacing(0); //vertical spacing between widgets
    bank_features -> setAlignment(Qt::AlignTop);
    bank_features -> addSpacing(20);
    bank_features -> addWidget(about_us);
    bank_features -> addSpacing(30);
    bank_features -> addWidget(info);
    bank_features -> addSpacing(35);
    bank_features -> addWidget(exchange);
    bank_features -> addSpacing(30);
    bank_features -> addWidget(table_exchange);
    bank_features -> addSpacing(30);
}

void Account::setting_pictures_for_echange() {
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

    table_exchange -> setStyleSheet("color: white; font-size: 22px; border: none; ");
    table_exchange -> setColumnWidth(0, 80); // to make 0r column less wider

    table_exchange -> verticalHeader() -> setVisible(false);
    table_exchange -> horizontalHeader() -> setVisible(false);
}

void Account::create_logo_button(QHBoxLayout* hbox, QPushButton* button, QLabel* label, const QString& image_path) {

    button -> setStyleSheet("border: none; font-size: 30px; color: white; text-align: left; padding-left: 30px;");
    QPixmap image(image_path);
    if (image.isNull()) {
        qDebug() << "Error loading image!";
    } else {
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
    add_logo_and_button_in_one_line(hbox, label, button);

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
    delete exchange;
    delete usd_label;
    delete eur_label;
    delete uah_label;
    for (int row = 0; row < table_exchange -> rowCount(); ++row) {
        for (int col = 1; col <= 3; ++col) {
            QTableWidgetItem* item = table_exchange -> item(row, col);
            if (item) {
                delete item;
            }
        }
    }
    delete table_exchange;
    delete name_surname_label;
    delete my_cards;
    delete apply_for_cards;
    delete card_label;
    delete business_card;
    delete visa_card;
    delete business_card_image;
    delete visa_card_image;
    delete apply_business_card;
    delete apply_visa_card;
    delete group_box_layout;
    delete center;
    delete bank_features;
    delete layout;
    delete buttons_widget;
    delete centeral_screen;
    delete features_widget;

}
