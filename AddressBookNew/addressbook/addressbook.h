#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QMap>
#include <QString>

#include <QMessageBox>

enum Mode{NavigationMode,AddingMode,EditingMode};

class AddressBook : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBook(QWidget *parent = nullptr);

signals:

public slots:
    void addContact();
    void submitContact();
    void cancel();
    void previous();
    void next();
    void editContact();
    void removeContact();

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *editButton;
    QPushButton *removeButton;

    QMap<QString,QString> contacts;
    QString oldName;
    QString oldAddress;
    Mode currentMode;

    void updateInterface(Mode mode);


};

#endif // ADDRESSBOOK_H
