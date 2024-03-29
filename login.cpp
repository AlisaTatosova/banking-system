#include "login.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QDebug>
#include "registration.h"
#include "account.h"

Login::Login(QWidget *parent) : QWidget(parent), db(DbManager::instance().get_database()) {
    setWindowTitle("Login window");
    setWindowFlags(this -> windowFlags() & ~Qt::WindowMinimizeButtonHint);
    QRect screen = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(screen);
    this -> setStyleSheet("background-color: black;");

    window = new QWidget;
    window -> setFixedSize(510, 580);
    window -> setStyleSheet("border: 2px solid gray; border-radius: 15px;");

    sign_in = new QLabel("Sign in");
    sign_in -> setStyleSheet("margin-right: 35px; color: white; font-size: 45px; border: none; ");

    username_edit = new QLineEdit;
    set_linedit(username_edit, "Enter username");

    password_edit = new QLineEdit;
    set_linedit(password_edit, "Enter password", true);

    login_status = new QLabel();
    password_status = new QLabel();
    login_status -> setStyleSheet("padding: 5px; border: none; color: white; font-size: 12px;");  
    password_status -> setStyleSheet("padding: 5px; border: none; color: white; font-size: 12px;");

    show_password_button = new QPushButton();
    password_layout = new QHBoxLayout;
    set_password();

    remember_me_checkbox = new QCheckBox("Remember Me");
    remember_me_checkbox -> setStyleSheet("margin-left: 5px; padding: 5px; color: white; font-size: 15px; border: none; ");

    forgett_password_button = new QPushButton("Forget password");
    forgett_password_button -> setFixedHeight(50); // Adjusted width and height
    forgett_password_button -> setStyleSheet("margin-right: 40px; border: none; border-radius: 15px; font-size: 15px; color: white; background-color: black; ");
    connect(forgett_password_button, &QPushButton::clicked, this, &Login::forgett_password_button_cliked);

    // Add Remember Me checkbox and Register button in the same line
    remember_forgetpassword_layout = new QHBoxLayout;
    remember_forgetpassword_layout -> addWidget(remember_me_checkbox);
    remember_forgetpassword_layout -> addStretch(); // Adding a stretch to separate Remember Me and forget password
    remember_forgetpassword_layout -> addWidget(forgett_password_button);

    login_button = new QPushButton("Login");
    set_login_button();

    register_button = new QPushButton("Create account");
    set_register_button();

    terminal = new QPushButton("Terminal");
    terminal -> setFixedSize(210, 40);
    terminal -> setStyleSheet("margin-right: 80px; border: none; border-radius: 15px; font-size: 15px; color: white; background-color: black; ");
    connect(terminal, &QPushButton::clicked, this, &Login::terminal_cliked);

    group_box_layout = new QVBoxLayout(window);
    add_to_group_box();

    layout = new QVBoxLayout(this);
    set_layout();
    logo_image = new QLabel(this);
    set_logo();

}

void Login::set_layout() {
    QRect screen = QApplication::desktop() -> screenGeometry();
    int x = screen.width() / 2 - 300;
    int y = screen.height() / 2 - 650;

    // for adding space beetween left board of groupbox and left board of linedit
    QMargins group_box_margins = window -> contentsMargins();
    group_box_margins.setLeft(30);
    window -> setContentsMargins(group_box_margins);
    layout -> setContentsMargins(x, y,  0, 0);
    layout -> addWidget(window);
}

void Login::set_login_button() {
    login_button -> setFixedSize(420, 45);
    login_button -> setStyleSheet("border: 2px solid grey; border-radius: 15px; font-size: 20px; color: white; background-color: black;");
    connect(login_button, &QPushButton::clicked, this, &Login::authenticate);
}

void Login::set_register_button() {
    register_button -> setFixedSize(210, 40);
    register_button -> setStyleSheet("margin-right: 80px; border: none; border-radius: 15px; font-size: 15px; color: white; background-color: black; ");
    connect(register_button, &QPushButton::clicked, this, &Login::register_cliked);
}

void Login::set_logo() {
    QRect screen = QApplication::desktop() -> screenGeometry();
    QPixmap image(":/images/logo2.png");
    if (image.isNull()) {
        qDebug() << "Error loading image!";
    } else {
        logo_image -> setPixmap(image);
        logo_image -> setGeometry(screen.width() / 2 - 150, screen.height() / 2 - 400, 200, 200);
    }
}

void Login::inputing_field(const QString& text, QLineEdit* line_edit, const QString& message) {
    if (text.isEmpty()) {
        line_edit -> setPlaceholderText(message);
    } else {
        line_edit -> setPlaceholderText("");
    }
}

void Login::set_placeholder_color(QLineEdit* line_edit, const QString& text, const QColor& color) {
    QPalette palette = line_edit -> palette();
    palette.setColor(QPalette::PlaceholderText, color);
    line_edit -> setPalette(palette);
    line_edit -> setPlaceholderText(text);
}

void Login::show_password_click() {
    if (password_edit -> echoMode() == QLineEdit::Password) {
        password_edit -> setEchoMode(QLineEdit::Normal);
        show_password_button -> setIcon(QIcon(":/images/open_eye.png"));
    } else {
        password_edit -> setEchoMode(QLineEdit::Password);
        show_password_button -> setIcon(QIcon(":/images/eye_icon.png"));
    }
}

void Login::terminal_cliked() {

}

void Login::authenticate() {
    // Get the entered username and password
    QString username = username_edit -> text();
    QString password = password_edit -> text();

    // Open the database
    if (!db.open()) {
        qDebug() << "Error: Could not open database.";
        qDebug() << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Clients WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        login_status -> setText("Authentication successful!");
        password_status -> setText("Authentication successful!"); // Authentication successful
        login_status -> setStyleSheet("padding: 5px; border: none; color: green; font-size: 12px;");
        password_status -> setStyleSheet("padding: 5px; border: none; color: green; font-size: 12px;");
        QString name = retrieve_name(username);
        QString surname = retrieve_surname(username);
        Account account(nullptr, name, surname, username);
        account.exec();
    } else {
        login_status -> setText("*Authentication failed. Invalid username or password."); // Authentication failed
        password_status -> setText("*Authentication failed. Invalid username or password."); // Authentication failed
        login_status -> setStyleSheet("padding: 5px; border: none; color: red; font-size: 12px;");
        password_status -> setStyleSheet("padding: 5px; border: none; color: red; font-size: 12px;");
    }

    // close the database
    db.close();
}


void Login::register_cliked() {
    Registration reg;
    reg.setModal(true);
    reg.exec();
}


void Login::forgett_password_button_cliked() {

}

QString Login::retrieve_name(const QString& username) {
    QString name;
    QSqlQuery query(db);

    // Prepare a SELECT query to retrieve the name based on the username
    query.prepare("SELECT name FROM clients WHERE username = :username");
    query.bindValue(":username", username);

    // Execute the query
    if (query.exec() && query.next()) {
        name = query.value("name").toString();
    } else {
        qDebug() << "Error retrieving user name:" << query.lastError().text();
    }

    return name;
}

QString Login::retrieve_surname(const QString& username) {
    QString surname;

    QSqlQuery query(db);
    query.prepare("SELECT surname FROM clients WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        surname = query.value("surname").toString();
    } else {
        qDebug() << "Error retrieving user surname:" << query.lastError().text();
    }

    return surname;
}

void Login::set_linedit(QLineEdit* line_edit, const QString& placeholder, bool is_password) {
    line_edit -> setFixedSize(420, 45);
    line_edit -> setStyleSheet("border: 2px solid gray; border-radius: 15px; font-size: 20px; color: white; padding: 5px;");
    set_placeholder_color(line_edit, placeholder, Qt::gray);

    if (is_password) {
        line_edit -> setEchoMode(QLineEdit::Password);
    }

    connect(line_edit, &QLineEdit::textChanged, this, [=](const QString& text) {
        inputing_field(text, line_edit, placeholder);
    });
}

void Login::set_password() {
    show_password_button -> setIcon(QIcon(":/images/eye_icon.png"));
    show_password_button -> setFixedSize(30, 30);
    show_password_button -> setStyleSheet("border: none; background-color: transparent;");
    connect(show_password_button, &QPushButton::clicked, this, &Login::show_password_click);

    // Add eye icon to the layout with password_edit
    password_layout -> addWidget(password_edit);
    password_layout -> addWidget(show_password_button);

    // placing eye icon at the end of password_edit line
    QMargins margins = password_layout -> contentsMargins();
    margins.setRight(show_password_button -> width() + 15);
    password_layout -> setContentsMargins(margins);
}

void Login::add_to_group_box() {
    group_box_layout -> setSpacing(0); //vertical spacing between widgets
    group_box_layout -> setAlignment(Qt::AlignBottom);
    group_box_layout -> addWidget(terminal);

    group_box_layout -> addWidget(sign_in, 0, Qt::AlignHCenter); // Align to the top and center horizontally
    group_box_layout -> addSpacing(35);
    group_box_layout -> addWidget(username_edit);
    group_box_layout -> addWidget(login_status);
    group_box_layout -> addSpacing(15);
    group_box_layout -> addLayout(password_layout);
    group_box_layout -> addWidget(password_status);
    group_box_layout -> addSpacing(15);
    group_box_layout -> addLayout(remember_forgetpassword_layout);
    group_box_layout -> addSpacing(20);
    group_box_layout -> addWidget(login_button);
    group_box_layout -> addWidget(register_button);
    group_box_layout -> addSpacing(20);
}

Login::~Login() {
    delete sign_in;
    delete username_edit;
    delete password_edit;
    delete show_password_button;
    delete login_button;
    delete register_button;
    delete logo_image;
    delete remember_me_checkbox;
    delete login_status;
    delete password_status;
    delete forgett_password_button;
    delete password_layout;
    delete remember_forgetpassword_layout;
    delete group_box_layout;
    delete layout;
    delete window;
}







