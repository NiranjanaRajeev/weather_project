#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readConfigFile();
    connect(ui->pbConnect,SIGNAL(clicked()),this,SLOT(connectBroker()));
    connect(ui->pbAbo,SIGNAL(clicked()),this,SLOT(abonnement()));

    m_client = new QMqttClient(this);
    connect(m_client,SIGNAL(messageReceived(QByteArray,QMqttTopicName)),this,SLOT(newMessage(QByteArray,QMqttTopicName)));
    connect(m_client,&QMqttClient::connected,[=](){ui->textEdit->append("Connecté");});

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
void MainWindow::newMessage(QByteArray message, QMqttTopicName topic)
{
    // Convert the received message to a QString
    QString jsonStr = QString::fromUtf8(message);

    // Parse the JSON document
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

    // Check if the JSON document is valid and represents an object
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();

        // Extract specific fields from the JSON object
        if (jsonObj.contains("name")) {
            QString name = jsonObj.value("name").toString();
            ui->textEdit->append("City: " + name);
        }

        if (jsonObj.contains("time")) {
            QString time = jsonObj.value("time").toString();
            ui->textEdit->append("Time: " + time);
        }

        if (jsonObj.contains("temperature")) {
            double temperature = jsonObj.value("temperature").toDouble();
            ui->textEdit->append("Temperature: " + QString::number(temperature));
        }
        if (jsonObj.contains("temp_min")) {
            double tempMin = jsonObj.value("temp_min").toDouble();
            ui->textEdit->append("Min Temperature: " + QString::number(tempMin));
        }

        if (jsonObj.contains("temp_max")) {
            double tempMax = jsonObj.value("temp_max").toDouble();
            ui->textEdit->append("Max Temperature: " + QString::number(tempMax));
        }

        if (jsonObj.contains("humidity")) {
            double humidity = jsonObj.value("humidity").toDouble();
            ui->textEdit->append("Humidity: " + QString::number(humidity));
        }
    }
}

void MainWindow::connectBroker()
{
    m_client->setHostname(ui->leAdresse->text());
    m_client->setPort(ui->spinBox->value());
//m_client->setUsername(ui->leUser->text());
  //  m_client->setPassword(ui->lePassword->text());
    m_client->connectToHost();
}

void MainWindow::abonnement()
{
    m_client->subscribe(QMqttTopicFilter(ui->leAboTopic->text()));
}



