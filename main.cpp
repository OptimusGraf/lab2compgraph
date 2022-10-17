#include "widget.h"

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QWidget mainWidget;
	auto* mwidget = new widget(&mainWidget);
	auto* button = new QPushButton(QString::fromLocal8Bit("Проход точки"), &mainWidget);
	button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	auto* layout = new QHBoxLayout;
	layout->addWidget(mwidget);
	layout->addWidget(button);
	mainWidget.setLayout(layout);
	mainWidget.resize(926, 626);
	mainWidget.show();
	QObject::connect(button, &QPushButton::clicked, mwidget, [mwidget]() {
		if(mwidget->doPoint)
			mwidget->doPoint = false;
		else 
			mwidget->doPoint = true;
		});
	return a.exec();
}
