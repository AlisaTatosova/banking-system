#ifndef SUCCESSFULLREGISTRATION_H
#define SUCCESSFULLREGISTRATION_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class SuccessfullRegistration : public QDialog {
    Q_OBJECT

public:
    SuccessfullRegistration(QWidget *parent = nullptr, const QString& text = "");
    ~SuccessfullRegistration();

private:
    QVBoxLayout* layout;
    QLabel* success;
};

#endif // SUCCESSFULLREGISTRATION_H
