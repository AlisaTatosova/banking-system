#include "registration.h"
#include "ui_registration.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QVBoxLayout>

Registration::Registration(QWidget *parent) :
    QDialog(parent) ,
    db(DbManager::instance().get_database()) {
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    setWindowTitle("Registration  window");

    QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen);
    this->setStyleSheet("background-color: black;");

    int x = screen.width() / 2 - 430;
    int y = screen.height() / 2 - 650;

    l = new QWidget;
    l -> setFixedSize(800, 650);
    l -> setStyleSheet("border: 2px solid gray; border-radius: 15px;");
    group_box_layout = new QVBoxLayout(l);
    group_box_layout -> setSpacing(0);
    group_box_layout -> setAlignment(Qt::AlignBottom);

    registration = new QLabel("Registration");
    registration -> setStyleSheet("color: white; font-size: 50px; border: none; ");

    name_edit = new QLineEdit;
    set_lineedit_left(name_edit);

    set_placeholder_color(name_edit, " Enter name", Qt::gray);
    connect(name_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, name_edit, "Enter your name");
    });
    name_status = new QLabel();
    set_status_left(name_status);

    surname_edit = new QLineEdit;
    set_lineedit_right(surname_edit);
    set_placeholder_color(surname_edit, " Enter your surname", Qt::gray);
    connect(surname_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, surname_edit, "Enter your surname");
    });
    surname_status = new QLabel();
    set_status_right(surname_status);

    // name surname linedits in one line
    name_surname_layout = new QHBoxLayout;
    add_two_linedits_in_one_line(name_surname_layout, name_edit, surname_edit);

    // name and surname status in one line
    name_surname_status_layout = new QHBoxLayout;
    add_two_labels_in_one_line(name_surname_status_layout, name_status, surname_status);

    mail_edit = new QLineEdit;
    set_lineedit_left(mail_edit);
    set_placeholder_color(mail_edit, " Enter your email address", Qt::gray);
    connect(mail_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, mail_edit, "Enter your email address");
    });
    mail_status = new QLabel();
    set_status_left(mail_status);

    age_edit = new QLineEdit;
    set_lineedit_right(age_edit);
    set_placeholder_color(age_edit, " Enter your age", Qt::gray);
    connect(age_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, age_edit, "Enter your age");
    });
    age_status = new QLabel();
    set_status_right(age_status);

    mail_age_layout = new QHBoxLayout;
    add_two_linedits_in_one_line(mail_age_layout, mail_edit, age_edit);

    mail_age_status_layout = new QHBoxLayout;
    add_two_labels_in_one_line(mail_age_status_layout, mail_status, age_status);

    phone_edit = new QLineEdit;
    set_lineedit_left(phone_edit);
    set_placeholder_color(phone_edit, " Enter your phone number", Qt::gray);
    connect(phone_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, phone_edit, "Enter your phone number");
    });
    phone_status = new QLabel();
    set_status_left(phone_status);

    username_edit = new QLineEdit;
    set_lineedit_right(username_edit);
    set_placeholder_color(username_edit, " Enter your username", Qt::gray);
    connect(username_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, username_edit, "Enter your username");
    });

    username_status = new QLabel();
    set_status_right(username_status);

    phone_username_layout = new QHBoxLayout;
    add_two_linedits_in_one_line(phone_username_layout, phone_edit, username_edit);

    phone_username_status_layout = new QHBoxLayout;
    add_two_labels_in_one_line(phone_username_status_layout, phone_status, username_status);

    password_edit = new QLineEdit;
    set_lineedit_left(password_edit);
    set_placeholder_color(password_edit, " Enter your password", Qt::gray);
    connect(password_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, password_edit, "Enter your password");
    });
    password_status = new QLabel();
    set_status_left(password_status);

    password_repeat_edit = new QLineEdit;
    set_lineedit_right(password_repeat_edit);
    set_placeholder_color(password_repeat_edit, " Enter your password again", Qt::gray);
    connect(password_repeat_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, password_repeat_edit, "Repeat your password");
    });
    password_repeat_status = new QLabel();
    set_status_right(password_repeat_status);

    password_layout = new QHBoxLayout;
    add_two_linedits_in_one_line(password_layout, password_edit, password_repeat_edit);

    password_status_layout = new QHBoxLayout;
    add_two_labels_in_one_line(password_status_layout, password_status, password_repeat_status);

    registration_button = new QPushButton("registration");
    registration_button -> setFixedSize(600, 45);
    registration_button -> setStyleSheet("margin-left: 200px; border: 2px solid grey; border-radius: 15px; font-size: 20px; color: white; background-color: black;");

    connect(registration_button,  &QPushButton::clicked, this, &Registration::validate_registration);

    group_box_layout -> addWidget(registration, 0, Qt::AlignHCenter); // Align to the top and center horizontally
    group_box_layout->addSpacing(50);
   // group_box_layout -> addWidget(name_edit);
    group_box_layout -> addLayout(name_surname_layout);
   // group_box_layout->addSpacing(-5);
    group_box_layout -> addLayout(name_surname_status_layout);
    group_box_layout->addSpacing(10);
    group_box_layout -> addLayout(mail_age_layout);
    //group_box_layout->addSpacing(-35);
    group_box_layout -> addLayout(mail_age_status_layout);
    group_box_layout->addSpacing(10);
    group_box_layout -> addLayout(phone_username_layout);
    //group_box_layout->addSpacing(-35);
    group_box_layout -> addLayout(phone_username_status_layout);
    group_box_layout->addSpacing(10);
    group_box_layout -> addLayout(password_layout);
    //group_box_layout->addSpacing(-35);
     group_box_layout -> addLayout(password_status_layout);
    group_box_layout->addSpacing(40);
    //group_box_layout->addSpacing(30);
    group_box_layout -> addWidget(registration_button);

    group_box_layout->addSpacing(30);


    layout = new QVBoxLayout(this);
    layout -> setContentsMargins(x, y,  0, 0);
    layout -> addWidget(l);



    QPixmap image(":/images/logo2.png");

    if (image.isNull()) {
        qDebug() << "Error loading image!";
    } else {
        logo_image = new QLabel(this);
        logo_image -> setPixmap(image);
        logo_image -> setGeometry((screen.width()) / 2 - 145, (screen.height()) / 2 - 435, 200, 200);
    }

}

void Registration::inputing_field(const QString& text, QLineEdit* lineedit, const QString& message) {
    if (text.isEmpty()) {
        lineedit->setPlaceholderText(message);
    } else {
      //  usernane_edit->setStyleSheet("border: 2px solid gray; border-radius: 15px; font-size: 20px; color: white; padding: 5px;  background-color: black; selection-color: white;");
        lineedit->setPlaceholderText("");
    }
}

void Registration::set_placeholder_color(QLineEdit* lineEdit, const QString& text, const QColor& color) {
    QPalette palette = lineEdit->palette();
    palette.setColor(QPalette::PlaceholderText, color);
    lineEdit->setPalette(palette);
    lineEdit->setPlaceholderText(text);
}

void Registration::set_status_left(QLabel* label) {
   // label -> setFixedSize(370, 40);
    label -> setFixedWidth(370);
    label -> setStyleSheet("margin-left: 20px; border: none; padding: 5px;  color: white; font-size: 12px;");

}

void Registration::set_status_right(QLabel* label) {
   // label -> setFixedSize(370, 40);
    label -> setFixedWidth(370);
    label -> setStyleSheet("margin-right: 20px; border: none; padding: 5px; color: white; font-size: 12px;");
}

void Registration::add_two_labels_in_one_line(QHBoxLayout* layout, QLabel* first, QLabel* second) {
    layout -> addWidget(first);
    layout -> addStretch(); // Add a stretch to separate Remember Me and Register
    layout -> addWidget(second);
}

void Registration::add_two_linedits_in_one_line(QHBoxLayout* layout, QLineEdit* first, QLineEdit* second) {
    layout -> addWidget(first);
    layout -> addStretch(); // Add a stretch to separate Remember Me and Register
    layout -> addWidget(second);
}

void Registration::set_lineedit_left(QLineEdit* lineedit) {
    lineedit -> setFixedSize(370, 40);
    // de left board of groupbox and name_edit be far
    lineedit -> setStyleSheet("margin-left: 20px; border: 2px solid gray; border-radius: 15px; font-size: 20px; color: white; padding: 5px;"); // border-radius: 15px -> this makes the bords rounded, padding: 5px -> this makes starting the text in lineedit from little bit righter from board,

}

void Registration::set_lineedit_right(QLineEdit* lineedit) {
    lineedit -> setFixedSize(370, 40);
    lineedit -> setStyleSheet("margin-right: 20px; border: 2px solid gray; border-radius: 15px; font-size: 20px; color: white; padding: 5px;"); // border-radius: 15px -> this makes the bords rounded, padding: 5px -> this makes starting the text in lineedit from little bit righter from board,
}

void Registration::validate_registration() {
    QString first_name = name_edit -> text().trimmed();
    QString last_name = surname_edit -> text().trimmed();
    QString mail = mail_edit -> text().trimmed();
    QString age = age_edit -> text().trimmed();
    QString phone = phone_edit -> text().trimmed();
    QString username = username_edit -> text().trimmed();
    QString password = password_edit -> text().trimmed();
    QString password_repeat = password_repeat_edit -> text().trimmed();

    bool invalid = false;

    if (!is_valid_name(first_name)) {
        not_valid_field(name_status, "*invalid first name.");
        invalid = true;
    } else {
        valid_field(name_status, "+okay");
    }

    if (!is_valid_last_name(last_name)) {
        not_valid_field(surname_status, "*invalid last name.");
        invalid = true;
    } else {
        valid_field(surname_status, "+okay");
    }

    if (!is_valid_Email(mail)) {
        not_valid_field(mail_status, "*invalid email format.");
        invalid = true;
    } else {
        valid_field(mail_status, "+okay");
    }

    if (!is_valid_age(age)) {
        not_valid_field(age_status, "*invalid age");
        invalid = true;
    } else {
        valid_field(age_status, "+okay");
    }



    if (!is_valid_phone(phone)) {
        not_valid_field(phone_status, "*invalid phone number format (10 digits).");
        invalid = true;
    } else {
        valid_field(phone_status, "+okay");
    }


    if (!is_valid_username(username)) {
        not_valid_field(username_status, "*invalid phone number format (10 digits).");
        invalid = true;
    } else {
        valid_field(username_status, "+okay");
    }

    if (!is_valid_password(password)) {
        not_valid_field(password_status, "*invalid password format (minimum 6 characters).");
        invalid = true;
    } else {
        valid_field(password_status, "+okay");
    }

    if (!is_valid_password_repeat(password, password_repeat)) {
        not_valid_field(password_repeat_status, "*.....mi ban");
        invalid = true;
    } else {
        valid_field(password_repeat_status, "+okay");
    }


    if (invalid) {
        return;
    }
}

void Registration::not_valid_field(QLabel* status, const QString& message) {
    status -> setText(message);
    if (status == name_status || status == mail_status || status == phone_status || status == password_status) {
        status -> setStyleSheet("margin-left: 20px; padding: 5px; border: none; color: red; font-size: 12px;");
    } else {
        status -> setStyleSheet("margin-right: 20px; padding: 5px; border: none; color: red; font-size: 12px;");
    }

}

void Registration::valid_field(QLabel* status, const QString& message) {
    status -> setText(message);
    if (status == name_status || status == mail_status || status == phone_status || status == password_status) {
        status -> setStyleSheet("margin-left: 20px; padding: 5px; border: none; color: green; font-size: 12px;");
    } else {
        status -> setStyleSheet("margin-right: 20px; padding: 5px; border: none; color: green; font-size: 12px;");
    }
}

bool Registration::is_valid_age(const QString& age) {
    bool is_num = age.toInt(&is_num) > 0;
    bool valid_range = age.toInt() >= 1 && age.toInt() <= 150;

    return is_num && valid_range;
}


bool Registration::is_valid_name(const QString& name) {
    // checking if the name contains only letters
    QRegExp rx("^[a-zA-Z]+$");
    return rx.exactMatch(name);
}

bool Registration::is_valid_last_name(const QString& last_name) {
    QRegExp rx("^[a-zA-Z]+$");
    return rx.exactMatch(last_name);
}


bool Registration::is_valid_phone(const QString& phone) {
    // checking if the phone number is 10 digits
    QRegExp rx("^\\d{10}$");
    return rx.exactMatch(phone);
}

bool Registration::is_valid_Email(const QString& email) {
    // checking if the email follows a basic format
    QRegExp rx("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return rx.exactMatch(email);
}

bool Registration::is_valid_username(const QString& username) {
    // username validation logic
    QRegExp rx(".{6,}");
    return rx.exactMatch(username);
}

bool Registration::is_valid_password(const QString& password) {
    // password validation logic
    return password.length() >= 6;
}

bool Registration::is_valid_password_repeat(const QString& password, const QString& repeated_password) {
    // Check if the repeated password matches the original password
    return password == repeated_password;
}

Registration::~Registration() {
    delete registration;
    delete name_edit;
    delete surname_edit;
    delete mail_edit;
    delete age_edit;
    delete password_edit;
    delete username_edit;
    delete phone_edit;
    delete password_repeat_edit;
    delete registration_button;
    delete logo_image;
    delete name_status;
    delete surname_status;
    delete mail_status;
    delete age_status;
    delete phone_status;
    delete username_status;
    delete password_status;
    delete password_repeat_status;
    delete password_status_layout;
    delete password_layout;
    delete phone_username_status_layout;
    delete phone_username_layout;
    delete mail_age_status_layout;
    delete mail_age_layout;
    delete name_surname_status_layout;
    delete name_surname_layout;
    delete group_box_layout;
    delete layout;
    delete l;
}