#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readConfigFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readConfigFile()
{
    // Read the config.json file
    QFile configFile("/home/niranjana/Projet_Final/config.json");
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Handle error: failed to open the file
        return;
    }

    QByteArray fileData = configFile.readAll();
    configFile.close();

    // Parse the JSON data
    QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));
    if (jsonDoc.isNull())
    {
        // Handle error: failed to parse JSON data
        return;
    }

    // Access the JSON object
    QJsonObject jsonObj = jsonDoc.object();

    // Extract "general" object
    QJsonObject generalObj = jsonObj["general"].toObject();

    // Extract "cities" array
    QJsonArray citiesArray = generalObj["cities"].toArray();
    for (const QJsonValue& cityValue : citiesArray)
    {
        QString city = cityValue.toString();
        cities.append(city);
    }

    // Extract "table_params" array
    QJsonArray tableParamsArray = generalObj["table_params"].toArray();
    for (const QJsonValue& paramValue : tableParamsArray)
    {
        QString param = paramValue.toString();
        tableParams.append(param);
    }

    // Print the extracted values for verification
    qDebug() << "Cities:" << cities;
    qDebug() << "Table Params:" << tableParams;
}

