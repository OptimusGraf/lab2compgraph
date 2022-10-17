#include "widget.h"
#include <QWheelEvent>
widget::widget(QOpenGLWidget* parent)
	: QOpenGLWidget(parent), func(1000, 50)
{
	statusBar = new QStatusBar(this);
	statusBar->resize(250, 50);

	lineOfPeriod = new QLineEdit(this);
	lineOfPeriod->setPlaceholderText(QString::fromLocal8Bit("¬ведите количество периодов"));

	lineOfPoint = new QLineEdit(this);
	lineOfPoint->setPlaceholderText(QString::fromLocal8Bit("¬ведите количество видимых точек"));

	auto* layout = new QGridLayout;
	layout->addWidget(statusBar, 0, 0, Qt::AlignTop);
	layout->addWidget(lineOfPeriod, 1, 0);
	layout->addWidget(lineOfPoint, 1, 1);
	this->setLayout(layout);

}

widget::~widget()
{
	delete statusBar;
	delete lineOfPeriod;
	delete lineOfPoint;

}

void widget::initializeGL()
{
	this->setMouseTracking(true);
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->glClearColor(102.0 / 255, 102.0 / 255, 102.0 / 255, 1);
	glMatrixMode(GL_MODELVIEW);


}

void widget::resizeGL(int w, int h)
{
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->glViewport(0, 0, w, h);
}

void widget::paintGL()
{
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	scalingGraph();
	ShowStatus();

	drawOs(f);
	drawAProjection();
	drawFunction();
	drawACrosshair();


}

void widget::ShowStatus()
{
	qreal coordinatX, coordinatY;
	coordinatX = mousePosition.x() * abs(wheelScroll);
	coordinatY = func.calculateY(coordinatX);

	QString s = "X:" + QString::number(coordinatX);
	s += "\t Y:" + QString::number(coordinatY);
	statusBar->showMessage(s);
}


void widget::scalingGraph()
{
	if (wheelScroll > 0)
		glScaled(wheelScroll, wheelScroll, 1);
	else
		glScaled(1 / wheelScroll, 1 / wheelScroll, 1);
}

void widget::drawOs(QOpenGLFunctions* f)
{

	float ver_line[] = { 1,0,0,  0.9,0.05,0,   1,0,0,  0.9, -0.05,0,   -1,0,0,  1,0,0 };
	glPushMatrix();
	glLoadIdentity();
	glVertexPointer(3, GL_FLOAT, 0, ver_line);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor3d(248 / 255.0, 243 / 255.0, 43 / 255.0);
	glDrawArrays(GL_LINES, 0, 6);

	glRotatef(90, 0, 0, 1);

	glDrawArrays(GL_LINES, 0, 6);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();



}

void widget::drawFunction()
{
	if (func.getCountOfPeriod() % 2 == 0)
		glTranslated(func.getSizeOfPeriod() * func.getCountOfPeriod() / 2 * -1, 0, 0);
	else
		glTranslated(func.getSizeOfPeriod() * (func.getCountOfPeriod() - 1) / 2 * -1, 0, 0);

	for (int i = 0; i < func.getCountOfPeriod(); i++)
	{
		glPushMatrix();
		drawPeriod(i);
		glPopMatrix();
	}

}

void widget::drawPeriod(int i)
{

	glTranslated(func.getSizeOfPeriod() * i, 0, 0);
	glVertexPointer(2, GL_DOUBLE, 0, func.GetArrayOfPoint());
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3d(0, 1, 1);
	glDrawArrays(GL_LINE_STRIP, 0, func.getCountOfPoint());
	glDisableClientState(GL_VERTEX_ARRAY);
}

void widget::wheelEvent(QWheelEvent* event)
{
	event->accept();
	int delta = event->angleDelta().y() / 32;
	wheelScroll += delta;
	update();
}

void widget::mouseMoveEvent(QMouseEvent* event)
{
	event->accept();
	mousePosition = event->pos();

	coordinateTransformation(mousePosition);

	update();
}
void widget::mousePressEvent(QMouseEvent* event)
{
	event->accept();
	if (event->button() == Qt::LeftButton)
	{
		doProgection = true;
		mousePositionForClick = event->pos();
		coordinateTransformation(mousePositionForClick);
	}

}

void widget::coordinateTransformation(QPointF& Position)
{
	Position.setX((Position.x() - width() / 2.) / width() * 2);
	Position.setY((Position.y() - height() / 2.) / height() * -2);
}

void widget::RunOfPoint()
{
	if (doPoint)
	{

	}
}

void widget::drawACrosshair()
{
	float ver_line[] = { mousePosition.x(),-1,0,	mousePosition.x(),1,0,
		-1,mousePosition.y(),0,	1,mousePosition.y(),0 };
	glPushMatrix();
	glLoadIdentity();
	glVertexPointer(3, GL_FLOAT, 0, ver_line);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3d(211 / 255.0, 211 / 255.0, 211 / 255.0);
	glDrawArrays(GL_LINES, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();

}

void widget::drawAProjection()
{
	if (doProgection)
	{
		float ver_line[] = { mousePositionForClick.x(),-1,0,		mousePositionForClick.x(),1,0,
			-1,func.calculateY(mousePositionForClick.x() * abs(wheelScroll)),0,		 1,func.calculateY(mousePositionForClick.x() * abs(wheelScroll)),0 };

		glPushMatrix();
		glLoadIdentity();
		glVertexPointer(3, GL_FLOAT, 0, ver_line);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColor3d(0, 1, 0);
		glDrawArrays(GL_LINES, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}
}



