#pragma once

#include <QObject>
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsObject>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QtWidgets>



class BarGraph : public QGraphicsObject
{
	Q_OBJECT

	Q_PROPERTY(int fadeDuration READ fadeDuration WRITE setFadeDuration)

public:
	BarGraph(QGraphicsItem* parent = nullptr);

	QRectF boundingRect() const;
	void sleep(float seconds);

	// Getter
	void getDelay(qreal delay);
	void getSize(qreal size);

	void getLimitValue(qreal limit);

	qreal fadeDuration() const { return duration; }
	void setFadeDuration(qreal milliseconds) { duration = milliseconds; }


protected:

	void delayTime(QTimerEvent* event);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);



public slots:
	void getForceRandom(qreal force);


private:
	QTimer* timer;
	QPropertyAnimation delay_animation;
	int delayId;
	qreal mark_delay;
	qreal delay_value;
	qreal current_alpha;
	qreal duration;


	qreal angle;
	qreal Radius;
	qreal mark_size;
	qreal limit_value;

	qreal G1;
	qreal m_value;

	int x_axis;
	int y_axis;
};