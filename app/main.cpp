#include <QApplication>
#include <QMainWindow>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMainWindow w;

	QWidget* widget = new QWidget(&w);
	w.setCentralWidget(widget);
	w.show();

	return a.exec();
}

