#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "robot.h"
#include "client.h"


int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Company");
    db.setUserName("Pascal");  // Change to username
    db.setPassword("Superbror22!");  // Change to password
    db.open();

    QSqlQuery query = QSqlQuery(db);

    Robot robotgenerator;
    Client Client1;

    Client1.PrintTask();

    std::string AddNewTaskChecker = "Start";

    while (AddNewTaskChecker != "run") {

        std::cout << "If you want to add a task write [task] " << std::endl
                  << "If u want to add a robot and assign it a task write [robot]" << std::endl
                  << "If u want to stop adding stuff and run the program write [run]" << std::endl;
        std::cin >> AddNewTaskChecker;
        std::cout << std::endl;



        if(AddNewTaskChecker == "task"){

            //Tilføj en opgave
            query.exec("select * from task");
            int task_id_next_task = query.size()+1;
            std::cout << "Skriv hvilken opgave du vil tilføje og start navnet med '-' : ";
            /*
            char garbage;
            std::cin >> garbage;*/
            std::string str;
            std::getline(std::cin >> std::ws, str);
            std::cout << "Skriv hvor lang tid den nye opgave tager: ";
            int TimeNewTask;
            std::cin >> TimeNewTask;

            query.prepare("INSERT INTO task (task_id, description, time) "
                          "VALUES (:task_id, :description, :time)");
            query.bindValue(":task_id", task_id_next_task);
            query.bindValue(":description", str.c_str());
            query.bindValue(":time", TimeNewTask);
            query.exec();

            query.exec("SELECT * FROM task"); // fisk er her navnet på en tabel, ikke et schema
            while (query.next()) {
                int task_id = query.value(0).toInt();
                QString description = query.value(1).toString();
                int time = query.value(2).toInt();
                qDebug() << "task_id:" << task_id << "description:" << description << "time:" << time;
            }
            std::cout << std::endl;
        }
        else if (AddNewTaskChecker == "robot"){
            robotgenerator.RobotTask();
        }
    }
    robotgenerator.RunRobots();



    return 1;
}

