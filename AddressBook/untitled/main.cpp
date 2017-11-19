#include <QApplication>
#include "addressbook.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AddressBook *addressBook = new AddressBook;
    addressBook->show();

    return a.exec();
}
