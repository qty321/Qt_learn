#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMap>
#include <QString>

class AddressBook : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBook(QWidget *parent = 0);

signals:

public slots:
    void addContact();
    void submitContact();
    void cancel();
    void editContact();
    void removeContact();
    void previous();
    void next();

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *previousButton;
    QPushButton *nextButton;

    QMap<QString,QString> contacts;
    QString oldName;
    QString oldAddress;
};

#endif // ADDRESSBOOK_H
