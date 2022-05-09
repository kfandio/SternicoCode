#include "BarGraph.h"
#include <QtMath>
#include <ctime>


BarGraph::BarGraph(QGraphicsItem* parent) :QGraphicsObject{ parent }
{
	setFlag(ItemIsMovable);
	Radius = 500;
	mark_size = 200;

	limit_value = 70;

	timer = new QTimer;

	duration = 10;

	x_axis = 0;
	y_axis = 250;
}

// Get the delay time from NewAP
void BarGraph::getDelay(qreal delay) {

	duration = delay * 10;
}

// Get the random force from NewAP 
void BarGraph::getForceRandom(qreal force) {
	this->m_value = force;// / 100;
	update();

	if (m_value >= limit_value) {

		timer->start(1);
		do
		{
			current_alpha = 255;
			this->mark_delay = m_value / 100;

			G1 = mark_delay * 255;

		} while (m_value < limit_value);

	}
	current_alpha -= 255 * timer->interval() / duration;
	

	if (current_alpha <= 0) {
		current_alpha = 0;
	}

}


/*
void HaftCircle::sleep(float seconds) {
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	while (clock() < startClock + secondsAhead);
	return;
}
*/

// Get the size from NewAP
void BarGraph::getSize(qreal size) {

	Radius = size;

}

// get the limit value from NewAP
void BarGraph::getLimitValue(qreal limit) {

	limit_value = limit;
}


// Part to paint the Feedback variant "Tacho/Gauge"


QRectF BarGraph::boundingRect() const
{
	return QRectF(0, 0, (Radius * 2) + 1000 + (mark_size * 2), (Radius * 2) + (mark_size * 10));
}


void  BarGraph::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

painter->translate(mark_size + 50, mark_size + 50);
painter->setRenderHint(QPainter::Antialiasing);


// Color Variation

QLinearGradient linearGradient(QPointF(x_axis, 0), QPointF(Radius*3, 0));
linearGradient.setColorAt(0, Qt::green);
linearGradient.setColorAt(0.5, Qt::yellow);
linearGradient.setColorAt(1, Qt::red);
QBrush brush(linearGradient);


// Color Variation delay

QLinearGradient linearGradient_1(QPointF(x_axis, 0), QPointF(Radius*3, y_axis));
linearGradient_1.setColorAt(0, QColor(0, 255, 0, current_alpha));
linearGradient_1.setColorAt(0.5, QColor(255, G1, 0, current_alpha));
linearGradient_1.setColorAt(1, QColor(255, 0, 0, current_alpha));
QBrush brush_1(linearGradient_1);


// Zeichnung von Füllung und Markierung
QPainterPath rect, full_delay, mark;
QPen pen, pen_rect, pen_delay, pen2;


qreal mark_value = Radius*3 * (m_value / 100);
pen_rect.setWidth(Radius);
pen_rect.setBrush(QColor(255, 0, 0, 0));


painter->setPen(pen_rect);
painter->setBrush(brush);
painter->drawRect(x_axis, 0, x_axis +  mark_value, Radius);

qreal fade_delay = mark_delay * Radius*3;

painter->setBrush(brush_1);
painter->drawRect(x_axis, 0, x_axis + fade_delay, Radius);



pen.setWidth(5);
pen.setColor(QColor("#d7d7d7"));
pen.setCapStyle(Qt::FlatCap);
rect.addRect(QRect(x_axis, 0 , Radius*3, Radius));
painter->strokePath(rect, pen);



//Mark
mark.moveTo(x_axis, Radius*3);
mark.arcTo(QRectF(x_axis, y_axis, 250, 250), 0, 180);
pen2.setWidth(mark_size);
pen2.setColor(QColor("#d7d7d7"));
pen2.setCapStyle(Qt::FlatCap);
pen2.setDashPattern(QVector<qreal>{0.1, 0.9});
//pen2.setDashOffset(2.2);
//painter->strokePath(mark, pen2);



// Text force
QPen pen5;
QFont font = painter->font();
QString force = QString::number(m_value, 'f', 1);

pen5.setColor(QColor("#d7d7d7"));
painter->setPen(pen5);
font.setPixelSize(100);

painter->setFont(font);
painter->drawText(QPointF(x_axis + Radius + 150, 0), force);


// Text Value
QPen pen6;
QFont font2 = painter->font();
pen6.setColor(QColor("#d7d7d7"));
painter->setPen(pen6);
font2.setPixelSize(100);

painter->setFont(font2);
painter->drawText(QPointF(x_axis, Radius + 100), tr("0"));
painter->drawText(QPointF(x_axis + Radius +150, Radius + 100), tr("50"));
painter->drawText(QPointF(x_axis + (Radius*3) -100, Radius +100), tr("100"));
}