#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLabel mylabel("Hello the World");
    mylabel.show();

    QPushButton hello("Hello World");
    hello.resize(100,30);
    hello.show();

    return a.exec();
}
