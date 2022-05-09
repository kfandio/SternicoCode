#pragma once

#include <QMainWindow>
#include "ui_NewAP.h"
#include "monitorthread.h"
#include "ThreadStorage.h"
#include <QtCore>
#include <QtGui>

#include <qcustomplot.h>

#include <QDir>
//#include <QDialog>
#include <QFileDialog>
#include <QStandardItemModel>


#include "HaftCircle.h"
#include "HalbCircleGradient.h"
#include "BarGraph.h"
#include "Circle.h"

#include "qvector.h"
#include "qmutex.h"

#include <QFile>
#include <QTextStream>

class NewAP : public QMainWindow
{
	Q_OBJECT
		
	Q_PROPERTY(qreal valueRandomForce READ valueRandomForce WRITE setValueRandomForce)
public:
	NewAP(ActorThread* ATPointer, MonitorThread* MTPointer, ThreadStorage* ReadDataPointer, QWidget *parent = Q_NULLPTR);
	~NewAP();

	void setforce();


	qreal valueRandomForce() const;
	

	QMutex ThreadMutex;
	QMutex ThreadStatusMutex;


	QLocale GetLocale();


	void NewAP::writecsv();

	void getColumn();
	void getRow();

	
	private slots:
		void escfullscreen();
		void makeFullScreen();
		void on_actionExit_triggered();

		void updateTime();

		void on_start_clicked();
		void on_stop_clicked();
		void setValueRandomForce(qreal value);

		void plotdata();

		void on_ok_clicked();

		void on_save_clicked();


protected:
	void timerEvent(QTimerEvent* event);

//signals:
//	void start();
	

private:
	Ui::NewAP ui;


	//Pointer
	MonitorThread* MT;
	ThreadStorage* InfoStorage;
	ActorThread* AT;


	QGraphicsScene* scene;
	QCustomPlot* plot;


	QTimer* timer;
	QTime* startTime;

	HaftCircle* halb_circle;
	HalbCircleGradient* halb_circle_gradient;
	BarGraph* bar;
	Circle* circle;


	QPropertyAnimation m_animation;

	QString Path;


	//Variabel
	int m_valueTimerId;
	qreal m_value;
	qreal newValue;

	qreal FramePS;

	std::vector<std::vector<QString>> Row;
	std::vector<QString> ColumnName;
	QString FileName;

	double key;

	qreal limit_value;
	
};	
