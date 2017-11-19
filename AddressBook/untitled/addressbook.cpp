#include "addressbook.h"

AddressBook::AddressBook(QWidget *parent) :
    QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);

    QLabel *addressLabel = new QLabel(tr("Address:"));
    addressText = new QTextEdit;
    addressText->setReadOnly(true);

    addButton = new QPushButton(tr("&Add"));
    addButton->show();
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();
    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);
    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);

    connect(addButton,SIGNAL(clicked()),this,SLOT(addContact()));
    connect(submitButton,SIGNAL(clicked()),this,SLOT(submitContact()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(editButton,SIGNAL(clicked()),this,SLOT(editContact()));
    connect(removeButton,SIGNAL(clicked()),this,SLOT(removeContact()));
    connect(previousButton,SIGNAL(clicked()),this,SLOT(previous()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(next()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addStretch();

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameLine,0,1);
    mainLayout->addWidget(addressLabel,1,0,Qt::AlignTop);
    mainLayout->addWidget(addressText,1,1);
    mainLayout->addLayout(buttonLayout1,1,2);
    mainLayout->addLayout(buttonLayout2,3,1);

    setLayout(mainLayout);
    setWindowTitle(tr("Simple Address Book"));
}

void AddressBook::addContact()
{
    oldName = nameLine->text();
    nameLine->clear();
    nameLine->setReadOnly(false);
    nameLine->setFocus(Qt::OtherFocusReason);
    oldAddress = addressText->toPlainText();
    addressText->clear();
    addressText->setReadOnly(false);
    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
}

void AddressBook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();
    if(name == "" || address == "") {
        QMessageBox::information(this,tr("Empty Field"),
                tr("Please enter a name and address"));
        return;
    }
    if(!contacts.contains(name)) {
        contacts.insert(name,address);
        QMessageBox::information(this,tr("Add Successful"),
                tr("\"%1\" has been added to your address book.").arg(name));
    } else {
        QMessageBox::information(this,tr("Add Unsuccessful"),
                tr("Sorry, \"%1\" is already in your address book.").arg(name));
        return;
    }
    if(contacts.isEmpty()) {
        nameLine->clear();
        addressText->clear();
    }
    nameLine->isReadOnly(true);
    addressText->isReadOnly(true);
    addButton->isEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}

void AddressBook::cancel()
{
    nameLine->setText(oldName);
    nameLine->isReadOnly(true);
    addressText->setText(oldAddress);
    addressText->isReadOnly(true);
    addButton->isEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}
