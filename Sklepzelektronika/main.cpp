#include <QtWidgets/QApplication>
#include <mysql.h>
#include <iostream>
#include "aplikacja_sklepu.h"

#include <QApplication>





using namespace std;

int qstate;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	aplikacja_sklepu w;
    w.show();




	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "kapi2798", "sklep elektroniczny", 3306, NULL, 0);

	if (conn) {
		cout << "Successful connection to database!" << endl;

		string query = "SELECT * FROM adresy";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}

	return a.exec();
}
