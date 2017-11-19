#include "addressbook.h"

AddressBook::AddressBook(QWidget *parent) : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);
    QLabel *addressLabel = new QLabel(tr("Address"));
    addressText = new QTextEdit;
    addressText->setReadOnly(true);
    addButton = new QPushButton(tr("&Add"));
    addButton->show();
    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);
    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);

    connect(addButton,SIGNAL(clicked()),this,SLOT(addContact()));
    connect(editButton,SIGNAL(clicked()),this,SLOT(editContact()));
    connect(removeButton,SIGNAL(clicked()),this,SLOT(removeContact()));
    connect(submitButton,SIGNAL(clicked()),this,SLOT(submitContact()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(previousButton,SIGNAL(clicked()),this,SLOT(previous()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(next()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton,Qt::AlignTop);
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
    mainLayout->addWidget(addressLabel,1,0);
    mainLayout->addWidget(addressText,1,1,Qt::AlignTop);
    mainLayout->addLayout(buttonLayout1,1,2);
    mainLayout->addLayout(buttonLayout2,2,1);
    setLayout(mainLayout);
    setWindowTitle(tr("Simple Address Book"));
}

void AddressBook::addContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();
    nameLine->clear();
    addressText->clear();
    nameLine->setReadOnly(false);
    nameLine->setFocus(Qt::OtherFocusReason);
    addressText->setReadOnly(false);
    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
    currentMode = AddingMode;
}

void AddressBook::editContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();
    updateInterface(EditingMode);
}

void AddressBook::removeContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();
    if(contacts.contains(name)){
        int button = QMessageBox::question(this,
            tr("Confirm Remove"),
            tr("Are you sure you want to remove \"%1\"?").arg(name),
            QMessageBox::Yes | QMessageBox::No);
        if(button == QMessageBox::Yes){
            previous();
            contacts.remove(name);
            QMessageBox::information(this,tr("Remove Successful"),
                tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }
    updateInterface(NavigationMode);
}

void AddressBook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();
    if(name == "" || address == ""){
        QMessageBox::information(this,tr("Empty Field"),tr("Please enter a name and address."));
        return;
    }
    if(currentMode == AddingMode){
        if(!contacts.contains(name)){
            contacts.insert(name,address);
            QMessageBox::information(this,tr("Add Successful"),tr("\"%1\" has been added to your address book.").arg(name));
        } else {
            QMessageBox::information(this,tr("Add Unsuccessful"),tr("Sorry, \"%1\" is already in your address book.").arg(name));
            return;
        }
    } else if(currentMode == EditingMode){
        if(oldName != name){
            if(!contacts.contains(name)){
                QMessageBox::information(this,tr("Edit Successful"),tr("\"%1\" has been edited in your address book.").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name,address);
            } else {
                QMessageBox::information(this,tr("Edit Unsuccessful"),tr("Sorry, \"%1\" is already in your address book.").arg(name));
            }
        } else if(oldAddress != address){
            QMessageBox::information(this,tr("Edit Successful"),tr("\"%1\" has been edited in your address book.").arg(name));
            contacts[name] = address;
        }
    }
    updateInterface(NavigationMode);
}

void AddressBook::cancel()
{
    nameLine->setText(oldName);
    nameLine->setReadOnly(true);
    addressText->setText(oldAddress);
    addressText->setReadOnly(true);
    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}

void AddressBook::previous()
{
    QString name = nameLine->text();
    QMap<QString,QString>::iterator i = contacts.find(name);
    if(i == contacts.end()){
        nameLine->clear();
        addressText->clear();
        return;
    }
    if(i == contacts.begin())
        i = contacts.end();
    i--;
    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void AddressBook::next()
{
    QString name = nameLine->text();
    QMap<QString,QString>::iterator i = contacts.find(name);
    if(i != contacts.end())
        i++;
    if(i == contacts.end())
        i = contacts.begin();
    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void AddressBook::updateInterface(Mode mode)
{
    currentMode = mode;
    switch (currentMode) {
    case AddingMode:
    case EditingMode:
        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        addressText->setReadOnly(false);
        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);
        previousButton->setEnabled(false);
        nextButton->setEnabled(false);
        submitButton->show();
        cancelButton->show();
        break;
    case NavigationMode:
        if(contacts.isEmpty()){
            nameLine->clear();
            addressText->clear();
        }
        nameLine->setReadOnly(true);
        addressText->setReadOnly(true);
        addButton->setEnabled(true);
        int num = contacts.size();
        editButton->setEnabled(num >= 1);
        removeButton->setEnabled(num >= 1);
        previousButton->setEnabled(num > 1);
        nextButton->setEnabled(num > 1);
        submitButton->hide();
        cancelButton->hide();
        break;
    }
}
