#include "login.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QDebug>
#include "registration.h"

Login::Login(QWidget *parent) : QWidget(parent), db(DbManager::instance().get_database()) {
    setWindowTitle("Login window");
    QRect screen = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(screen);
    this -> setStyleSheet("background-color: black;");

    int x = screen.width() / 2 - 300;
    int y = screen.height() / 2 - 650;

    window = new QWidget;
    window -> setFixedSize(510, 580);
    window -> setStyleSheet("border: 2px solid gray; border-radius: 15px;");
    group_box_layout = new QVBoxLayout(window);

    group_box_layout -> setSpacing(0); //vertical spacing between widgets
    group_box_layout -> setAlignment(Qt::AlignBottom);

    sign_in = new QLabel("Sign in");
    sign_in -> setStyleSheet("margin-right: 35px; color: white; font-size: 45px; border: none; ");

    username_edit = new QLineEdit;
    username_edit -> setFixedSize(420, 45);
    username_edit -> setStyleSheet("border: 2px solid gray; border-radius: 15px; font-size: 20px; color: white; padding: 5px;"); // border-radius: 15px -> this makes the bords rounded, padding: 5px -> this makes starting the text in lineedit from little bit righter from board,
    set_placeholder_color(username_edit, " Enter username", Qt::gray);
    connect(username_edit, &QLineEdit::textChanged, this, &Login::inputing_username);

    login_status = new QLabel();
    login_status -> setStyleSheet("padding: 5px; border: none; color: white; font-size: 12px;");

    password_edit = new QLineEdit;
    password_edit -> setFixedSize(420, 45);
    password_edit -> setStyleSheet("border: 2px solid gray; border-radius: 15px; font-size: 20px; color: white; padding: 5px;");
    set_placeholder_color(password_edit, " Enter password", Qt::gray);
    password_edit -> setEchoMode(QLineEdit::Password);
    connect(password_edit, &QLineEdit::textChanged, this, &Login::inputing_password);

    password_status = new QLabel();
    password_status -> setStyleSheet("padding: 5px; border: none; color: white; font-size: 12px;");

    show_password_button = new QPushButton();
    show_password_button -> setIcon(QIcon(":/images/eye_icon.png"));
    show_password_button -> setFixedSize(30, 30);
    show_password_button -> setStyleSheet("border: none; background-color: transparent;");
    connect(show_password_button, &QPushButton::clicked, this, &Login::show_password_click);

    // Add eye icon to the layout with password_edit
    password_layout = new QHBoxLayout;
    password_layout -> addWidget(password_edit);
    password_layout -> addWidget(show_password_button);

    // placing eye icon at the end of password_edit line
    QMargins margins = password_layout -> contentsMargins();
    margins.setRight(show_password_button -> width() + 15);
    password_layout -> setContentsMargins(margins);

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
    login_button -> setFixedSize(420, 45);
    login_button -> setStyleSheet("border: 2px solid grey; border-radius: 15px; font-size: 20px; color: white; background-color: black;");
    connect(login_button, &QPushButton::clicked, this, &Login::authenticate);

    register_button = new QPushButton("Create account");
    register_button -> setFixedSize(210, 40);
    register_button -> setStyleSheet("margin-right: 80px; border: none; border-radius: 15px; font-size: 15px; color: white; background-color: black; ");
    connect(register_button, &QPushButton::clicked, this, &Login::register_cliked);

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

    // for adding space beetween left board of groupbox and left board of linedit
    QMargins groupBoxMargins = window -> contentsMargins();
    groupBoxMargins.setLeft(30);
    window -> setContentsMargins(groupBoxMargins);

    layout = new QVBoxLayout(this);
    layout -> setContentsMargins(x, y,  0, 0);
    layout -> addWidget(window);


    QPixmap image(":/images/logo2.png");
    if (image.isNull()) {
        qDebug() << "Error loading image!";
    } else {
        logo_image = new QLabel(this);
        logo_image -> setPixmap(image);
        logo_image -> setGeometry(screen.width() / 2 - 150, screen.height() / 2 - 400, 200, 200);
    }
}

void Login::inputing_username(const QString& text) {
    if (text.isEmpty()) {
        username_edit -> setPlaceholderText("Enter username");
    } else {
        username_edit -> setPlaceholderText("");
    }
}

void Login::inputing_password(const QString& text) {
    if (text.isEmpty()) {
        password_edit -> setPlaceholderText("Enter password");
    } else {
        password_edit -> setPlaceholderText("");
    }
}

void Login::set_placeholder_color(QLineEdit* lineEdit, const QString& text, const QColor& color) {
    QPalette palette = lineEdit -> palette();
    palette.setColor(QPalette::PlaceholderText, color);
    lineEdit -> setPalette(palette);
    lineEdit -> setPlaceholderText(text);
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
    query.prepare("SELECT * FROM Clients WHERE Username = :username AND Password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        login_status -> setText("Authentication successful!");
        password_status -> setText("Authentication successful!"); // Authentication successful
        login_status -> setStyleSheet("padding: 5px; border: none; color: green; font-size: 12px;");
        password_status -> setStyleSheet("padding: 5px; border: none; color: green; font-size: 12px;");
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







