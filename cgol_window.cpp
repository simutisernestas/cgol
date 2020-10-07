#include "cgol_window.hpp"
#include "./ui_cgol.h"

CGOLWindow::CGOLWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui::CGOLWindow), position_{0}
{
	ui->setupUi(this);
}

CGOLWindow::~CGOLWindow()
{
	delete ui;
}

void CGOLWindow::on_speedSlider_valueChanged(int position)
{
	printf("Slider positions: %d\n", position);
	position_ = position;
}

int CGOLWindow::getSpeed() const
{
	return position_;
}
