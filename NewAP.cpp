#include "NewAP.h"
#include <QDebug>
#include <QtMath>

NewAP::NewAP(ActorThread* ATPointer, MonitorThread* MTPointer, ThreadStorage* ReadDataPointer, QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Pointer
	this->AT = ATPointer;
	this->MT = MTPointer;
	this->InfoStorage = ReadDataPointer;



	timer = new QTimer;
	startTime = new QTime;

	

	scene = new QGraphicsScene(this);
	ui.graphicsView_halb_circle->setScene(scene);
	
	plotdata();

	halb_circle = new HaftCircle; // Tacho_1 Feedback 1
	halb_circle_gradient = new HalbCircleGradient; //Tacho_2 Feedback 2
	bar = new BarGraph;
	circle = new Circle;

	scene->addItem(halb_circle);


	connect(ui.forceValue1, &QSlider::valueChanged, 
		[=]() { halb_circle_gradient->getforce((qreal)ui.forceValue1->value() ); });

	connect(ui.full, SIGNAL(clicked()), this, SLOT(makeFullScreen()));
	new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(escfullscreen()));

	

	// setup a timer that repeatedly calls updateTime:
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));



	ui.time->setText(QTime(0, 0).toString());

	

	FramePS = 100;

	ui.stop->setEnabled(false);
	ui.save->setEnabled(false);
	limit_value = 70;
}

// Plot the live Data force
void NewAP::plotdata() {

	plot = new QCustomPlot;
	scene->addWidget(plot);

	plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
		QCP::iSelectLegend | QCP::iSelectPlottables);

	plot->setLocale(QLocale(QLocale::German, QLocale::Germany)); // period as decimal separator and comma as thousand separator
	plot->resize(800, 200);
	plot->yAxis->setRange(-5, 100);
	plot->axisRect()->setupFullAxesBox();

	plot->plotLayout()->insertRow(0);
	QCPTextElement* title = new QCPTextElement(plot, "Insertion force", QFont("sans", 10, QFont::Bold));
	plot->plotLayout()->addElement(0, 0, title);

	
	plot->legend->setVisible(true);
	QFont legendFont = font();  // start out with MainWindow's font..
	legendFont.setPointSize(9); // and make a bit smaller for legend
	plot->legend->setFont(legendFont);
	plot->legend->setBrush(QBrush(QColor(255, 255, 255, 155)));
	plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);

	plot->xAxis->setLabel("Time in ms");
	plot->yAxis->setLabel(" Force in mN");


	plot->addGraph();
	plot->graph(0)->setAntialiased(true);
	plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
	plot->graph(0)->setName("force");

	plot->addGraph();
	plot->graph(1)->setPen(QPen(Qt::red));
	plot->graph(1)->setLineStyle(QCPGraph::lsNone);
	plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
	plot->graph(1)->setName("peak");

	plot->graph(0)->rescaleValueAxis();
	plot->graph(1)->rescaleValueAxis(true);
	//QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	//timeTicker->setTimeFormat("%h:%m:%s");
	//plot->xAxis->setTicker(timeTicker);
	//plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);

	

	// make left and bottom axes transfer their ranges to right and top axes:
	//connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
	//connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

}

void NewAP::updateTime() 
{ 
	ui.time->setText(QTime(0, 0).addMSecs(startTime->elapsed()).toString()); 

	//static QTime time(QTime::currentTime());
	// calculate two new data points:
	//double key = time.elapsed() / 10; // time elapsed since start of demo, in seconds
	double key = startTime->elapsed()/ FramePS;// time elapsed since start of demo, in seconds

	//qDebug() << key;
	//static double lastPointKey = 0;
	

	//if (key - lastPointKey > 0.01) // at most add point every 100 ms
	//{
		//qDebug() << key;
		//qDebug() << m_value;
		// add data to lines:
		//double k = key / 10;
		plot->graph(0)->addData(key, m_value);

		// rescale value (vertical) axis to fit the current data:
		//ui->customPlot->graph(0)->rescaleValueAxis();
		//ui->customPlot->graph(1)->rescaleValueAxis(true);
		//lastPointKey = key;
	//}
	
	// make key axis range scroll with the data (at a constant range size of 8):
	
	if (m_value> limit_value)
	{	
		plot->graph(1)->addData(key, m_value);	
	}

	plot->xAxis->setRange(key, 1000, Qt::AlignRight);

	plot->replot();
	plot->update();
}


/*Generate Random force number each 100 ms see startTimer(100)*/
// Get the new value
void NewAP::on_start_clicked() 
{
	Row.clear();

	if (ui.variant->currentText() == "Tacho_1")
	{
		m_valueTimerId = startTimer(FramePS);
		m_value = 0;
		m_animation.setTargetObject(this);
		m_animation.setPropertyName("valueRandomForce");

		ui.time->setText(QTime(0, 0).toString());
		startTime->restart();
		timer->start(0);  // Interval 0 means to refresh as fast as possible

		updateTime();
	}
	else if (ui.variant->currentText() == "Tacho_2")
	{
		//halb_circle_gradient->getforceRandom_1(m_value);
	}
	else if (ui.variant->currentText() == "Bar")
	{
		m_valueTimerId = startTimer(FramePS);
		m_value = 0;
		m_animation.setTargetObject(this);
		m_animation.setPropertyName("valueRandomForce");

		ui.time->setText(QTime(0, 0).toString());
		startTime->restart();
		timer->start(0);  // Interval 0 means to refresh as fast as possible

		updateTime();
	}

	else if (ui.variant->currentText() == "Circle")
	{
		m_valueTimerId = startTimer(FramePS);
		m_value = 0;
		m_animation.setTargetObject(this);
		m_animation.setPropertyName("valueRandomForce");

		ui.time->setText(QTime(0, 0).toString());
		startTime->restart();
		timer->start(0);  // Interval 0 means to refresh as fast as possible

		updateTime();
	}
	
	
	ui.variant->setEnabled(false);
	ui.start->setEnabled(false);
	ui.stop->setEnabled(true);
	ui.save->setEnabled(false);
	ui.limit_value->setEnabled(false);
	ui.test_person->setEnabled(false);
	ui.startcolor->setEnabled(false);
	ui.endcolor->setEnabled(false);
}

void NewAP::on_stop_clicked() {
	m_valueTimerId = 0;
	m_value = 0;
	//newValue = 0;
	ui.delay->setValue(0);
	
	if (ui.variant->currentText() == "Tacho_1")
	{
		halb_circle->getForceRandom(m_value);
	}
	else if (ui.variant->currentText() == "Tacho_2") 
	{
		//halb_circle_gradient->getforceRandom_1(m_value);
	}
	else if (ui.variant->currentText() == "Bar")
	{
		bar->getForceRandom(m_value);
	}
	else if (ui.variant->currentText() == "Circle")
	{
		circle->getForceRandom(m_value);
	}
	
	timer->stop();
	ui.variant->setEnabled(true);
	ui.stop->setEnabled(false);
	ui.start->setEnabled(true);
	ui.save->setEnabled(true);
	ui.limit_value->setEnabled(true);
	ui.test_person->setEnabled(true);
	ui.startcolor->setEnabled(true);
	ui.endcolor->setEnabled(true);
}

qreal NewAP::valueRandomForce() const
{
	return m_value;
}

void NewAP::setValueRandomForce(qreal value)
{
	if (qFuzzyCompare(value, m_value))
		return;
	m_value = value;
	update();

	if (ui.variant->currentText() == "Tacho_1")
	{
		halb_circle->getForceRandom(m_value);
		//get Row force Data
		//getRow();
	}
	else if (ui.variant->currentText() == "Tacho_2")
	{
		//halb_circle_gradient->getforceRandom_1(m_value);
		
	}
	else if (ui.variant->currentText() == "Bar")
	{
		bar->getForceRandom(m_value);

	}
	else if (ui.variant->currentText() == "Circle")
	{
		circle->getForceRandom(m_value);

	}
}


void NewAP::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == m_valueTimerId)
	{
		//qreal alpha = qrand() % 180;
		//qreal h = qDegreesToRadians(alpha);

		//newValue = qSin(h);


		newValue = qrand() % 100;
		//qDebug() << newValue;
		//if (newValue > 100) newValue = 100;

		//qDebug() << m_value;
		
		m_animation.setStartValue(newValue);
		m_animation.setEndValue(newValue);
		m_animation.start();
	}

}




// Function for OK Buttom tp set all parameters

void NewAP::on_ok_clicked() {

	// Feedback variants
	// Delay , Size and Limit value
	int delay_time = ui.delay->value();
	int size_size = ui.size1->value();
	limit_value = ui.limit_value->value();
	if (ui.variant->currentText() == "Tacho_1")
	{
		scene->removeItem(halb_circle_gradient);
		scene->removeItem(bar);
		scene->removeItem(circle);
		scene->addItem(halb_circle);
		

		halb_circle->getDelay(delay_time);
		halb_circle->getSize(size_size);
		halb_circle->getLimitValue(limit_value);
	}
	else if (ui.variant->currentText() == "Tacho_2") 
	{
		scene->removeItem(halb_circle);
		scene->removeItem(bar);
		scene->removeItem(circle);
		scene->addItem(halb_circle_gradient);

		halb_circle_gradient->getDelay(delay_time);
		halb_circle_gradient->getSize(size_size);
		halb_circle_gradient->getLimitValue(limit_value);
	}
	else if (ui.variant->currentText() == "Bar")
	{
		scene->removeItem(halb_circle_gradient);
		scene->removeItem(halb_circle);
		scene->removeItem(circle);
		scene->addItem(bar);
		

		bar->getDelay(delay_time);
		bar->getSize(size_size);
		bar->getLimitValue(limit_value);
	}
	else if (ui.variant->currentText() == "Circle")
	{
		scene->removeItem(halb_circle_gradient);
		scene->removeItem(halb_circle);
		scene->removeItem(bar);
		scene->addItem(circle);



		circle->getSize(size_size);
		circle->getLimitValue(limit_value);
	}


	// Background
	if (ui.Backgroud1->currentText() == "White")
	{
		scene->setBackgroundBrush(Qt::white);
		plot->setBackground(Qt::white);
	}
	else if (ui.Backgroud1->currentText() == "Gray") 
	{
		scene->setBackgroundBrush(Qt::gray);
		plot->setBackground(Qt::gray);
	}
	else if (ui.Backgroud1->currentText() == "Black") 
	{
		scene->setBackgroundBrush(Qt::black);
		plot->setBackground(Qt::black);
	}
	else if (ui.Backgroud1->currentText() == "Red") 
	{
		scene->setBackgroundBrush(QColor("#7a524b"));
		plot->setBackground(QColor("#7a524b"));
	}

}

NewAP::~NewAP()
{
	
}




void NewAP::on_actionExit_triggered()
{
	QApplication::exit();
}



// write in csv
void NewAP::on_save_clicked() 
{
	this->writecsv();
}

//Generate first line
void NewAP::getColumn() {
//positions
	std::vector<QString> columnnames;

	columnnames.push_back(QString("Force [mN]"));

	//additional informations

	columnnames.push_back(QString("Timestamp [ms]"));
	columnnames.push_back(QString("Peak"));
	columnnames.push_back(QString("Variant"));
	columnnames.push_back(QString("Limit value [mN]"));
	columnnames.push_back(QString("Test Person"));
	ColumnName = columnnames;
}

// get Row ForceData
// run on setValueRandomForce()
void NewAP::getRow() {

	
	std::vector<QString> column;
	//forces
	column.push_back(QString::number(m_value * 1000, 'f', 0));
	column.push_back(QString::number(key * 10));
	column.push_back(ui.variant->currentText());
	Row.push_back(column);
}

// Write in CSV File
void NewAP::writecsv() {

	getColumn();

	auto file_name = QFileDialog::getSaveFileName(this, "Save",
		QDir::currentPath(), "CSV File (*.csv)");

	if (file_name.isEmpty()) {
		return;
	}
	QFile data(file_name);
	if (!data.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}

	QTextStream outputdata(&data);

	for (int i = 0; i < ColumnName.size(); i++)
	{
		outputdata << ColumnName.at(i) << ";";
	}
	outputdata << "\n";
	

	for (int row = 0; row < this->Row.size(); row++) {
		for (int column = 0; column < this->Row.at(row).size(); column++) 
		{	
			outputdata << this->Row.at(row).at(column) << ";";
		}
		outputdata << "\n";
	}

	data.flush();
	data.close();
}








// for Full Screen
void NewAP::makeFullScreen() 
{
	if (ui.viewfeedback->isFloating() == false) {
		ui.viewfeedback->setFloating(true);
		ui.viewfeedback->setWindowState(Qt::WindowMaximized);
	}
	if (ui.viewfeedback->isFullScreen() == false) {
		ui.viewfeedback->setWindowState(Qt::WindowFullScreen);
	}
	else if (ui.viewfeedback->isFullScreen() == true) {
		ui.viewfeedback->setWindowState(Qt::WindowMaximized);
	}
}

// Esc Full Screen
void NewAP::escfullscreen() 
{
	if (ui.viewfeedback->isFullScreen() == true) 
	{
		ui.viewfeedback->setWindowState(Qt::WindowMaximized);
	}
}
