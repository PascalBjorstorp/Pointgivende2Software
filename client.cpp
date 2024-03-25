#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "client.h"

Client::Client() {}


void Client::PrintTask(){

    QSqlDatabase db = QSqlDatabase::database("Company");

    QSqlQuery query = QSqlQuery(db);


    query.exec("SELECT * FROM task");
    while (query.next()) {
        int task_id = query.value(0).toInt();
        QString description = query.value(1).toString();
        int time = query.value(2).toInt();
        qDebug() << "task_id:" << task_id << "description:" << description << "time:" << time;
    }

}
