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
	widget(QWidget* parent = nullptr);
	~widget();
	bool doPoint = false;
private:
	void initializeGL() override;
	void paintGL() override;
	void ShowStatus();
	void scalingGraph();
	void resizeGL(int w, int h) override;

	void drawOs();

	void drawPeriod(int i);
	void drawFunction();
	void drawACrosshair();
	void RunOfPoint();
	void drawAProjection();

	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;


	double wheelScroll = 1.;
	FunctionTg func;
	QPointF mousePosition;
	QPointF mousePositionForClick;

	void coordinateTransformation(QPointF& Position);
	QPointF coordinateTransformationFrom0To1(QPointF Position);

	void changeCountOfPeriod(std::string s);
	void changeCountOfPoint(std::string s);
	bool isValue(std::string s);

	bool doProgection = false;

	int runningPoint;
	QStatusBar* statusBar;
	QLineEdit* lineOfPeriod;
	QLineEdit* lineOfPoint;
};
#endif // WIDGET_H
