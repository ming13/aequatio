#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"


/* 
	This class interconnects ui level and application level.
	Controller implements Singletone pattern.
*/
class Controller : public QObject
{
	Q_OBJECT
public:
	static Controller *instance();	
	int runApplication(int argc, char *argv[]);
signals:

public slots:
private slots:
	void commandEntered(const QString &command);
private:
	explicit Controller(QObject *parent = 0);
	static Controller *m_instance;
	MainWindow *m_mainWindow;
};

#endif // CONTROLLER_H