#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <vector>


#include "robot.h"
Robot::Robot() {}


void Robot::RobotTask()
{
    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

    std::string str2;
    int taskID;
    std::cout << "What do you want to name the robot: ";
    std::cin >> str2;
    std::cout << "What task do you want to assing it to: ";
    std::cin >> taskID;

    std::vector<int> TakenTask;
    TakenTask.clear();

    query.exec("SELECT current_task FROM robots");
    while (query.next()) {
        int current_task = query.value(0).toInt();
        TakenTask.push_back(current_task);
    }


    for (int i = 0; i <= TakenTask.size(); i++) {

        if (TakenTask.size() == 0){
            query.prepare("INSERT INTO robots ( name, current_task) "
                          "VALUES (:name, :current_task)");
            query.bindValue(":name", str2.c_str());
            query.bindValue(":current_task", taskID);
            query.exec();
        }

        else if (taskID == TakenTask[i]) {
            std::cout << "Task is taken" << std::endl << std::endl;
            return;
        }
        else{
            query.prepare("INSERT INTO robots ( name, current_task) "
                          "VALUES (:name, :current_task)");
            query.bindValue(":name", str2.c_str());
            query.bindValue(":current_task", taskID);
            query.exec();
        }
    }
    std::cout << std::endl;






}






void Robot::RunRobots(){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

    std::vector<int> CompletedRobotTask;
    std::vector<int> CompletedTask;
    CompletedRobotTask.clear();
    CompletedTask.clear();


    query.exec("SELECT task_id, current_task, name, description FROM task,robots WHERE task_id = current_task");
    while (query.next()) {
        int task_id = query.value(0).toInt();
        int current_task = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString description = query.value(3).toString();

        CompletedRobotTask.push_back(current_task);
        CompletedTask.push_back(task_id);
        std::cout << std::endl;
        qDebug() << name << " has been asigned to task with id of" << current_task
                 <<"The task with id" << task_id << " is" << description;
        qDebug() << name << " have now completed" << description;
        std::cout << std::endl;

    }
    std::cout << std::endl;

    for (int i = 0; i < CompletedRobotTask.size(); i++) {
        query.exec(QString("DELETE FROM task WHERE task_id = %1").arg(CompletedTask[i]));
        query.exec(QString("DELETE FROM robots WHERE current_task = %1").arg(CompletedRobotTask[i]));
    }

    std::cout << std::endl;
    std::cout << "Remaining tasks" << std::endl;
    query.exec("SELECT * FROM task");
    while (query.next()) {
        int task_id = query.value(0).toInt();
        QString description = query.value(1).toString();
        int time = query.value(2).toInt();
        qDebug() << "task_id:" << task_id << "description:" << description << "time:" << time;
    }

    //std::cout << "Robot self destruct!" << std::endl;
    query.exec("DELETE FROM robots WHERE current_task >= 0");
    //query.exec(QString("DELETE FROM robots WHERE current_task = 1").arg(taskID);


}

