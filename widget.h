#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QStatusBar>
#include <QLineEdit>
#include <QGridLayout>
#include "FunctionTg.h"
class widget : public QOpenGLWidget
{
	Q_OBJECT

public:
	widget(QOpenGLWidget* parent = nullptr);
	~widget();
private:
	void initializeGL() override;
	void paintGL() override;
	void ShowStatus();
	void scalingGraph();
	void resizeGL(int w, int h) override;

	void drawOs(QOpenGLFunctions* f);
	FunctionTg func;
	void drawPeriod(int i);
	void drawFunction();

	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

	

	double wheelScroll = 1.;

	QPointF mousePosition;
	void coordinateTransformation(QPointF& Position);
	QPointF coordinateTransformationFrom0To1(QPointF Position);

	bool doPoint = false;
	void RunOfPoint();
	QPointF runnigPoint;

	void drawACrosshair();


	void drawAProjection();
	bool doProgection = false;
	QPointF mousePositionForClick;

	QStatusBar* statusBar;
	QLineEdit* lineOfPeriod;
	QLineEdit* lineOfPoint;
};
#endif // WIDGET_H
