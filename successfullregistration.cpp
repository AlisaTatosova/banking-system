// successfullregistration.cpp

#include "successfullregistration.h"
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QStyle>

SuccessfullRegistration::SuccessfullRegistration(QWidget *parent) : QDialog(parent) {
   setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    this -> setStyleSheet("background-color: black;");
    setMinimumSize(500, 200);

    layout = new QVBoxLayout(this);
    success = new QLabel(this);
    success -> setText("You are successfully registered!");
    success -> setStyleSheet("border: none; color: green; font-size: 30px;");

    layout -> addWidget(success);
    layout -> setSpacing(20);
    layout -> setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

SuccessfullRegistration::~SuccessfullRegistration() {
    delete success;
    delete layout;
}



