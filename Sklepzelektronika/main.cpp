#include <QtWidgets/QApplication>
#include <mysql.h>
#include <iostream>
#include "aplikacja_sklepu.h"
#include <iostream>
#include <QApplication>








using namespace std;

int qstate;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	aplikacja_sklepu w;
	w.show();	
	return a.exec();
}
