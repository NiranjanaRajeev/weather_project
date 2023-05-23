#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt/qmqttclient.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList cities;       // Member variable to store cities
    QStringList tableParams;
    void readConfigFile();
    QMqttClient* m_client = nullptr;

private slots:
    void newMessage(QByteArray message ,QMqttTopicName topic);
    void connectBroker();
    void abonnement();

};
#endif // MAINWINDOW_H
