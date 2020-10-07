#include "cgol_window.hpp"
#include "./ui_cgol.h"

CGOLWindow::CGOLWindow(QWidget *parent)
	: QWidget(parent), ui(new Ui::CGOLWindow)
{
	ui->setupUi(this);
}

CGOLWindow::~CGOLWindow()
{
	delete ui;
}

void CGOLWindow::on_speedSlider_valueChanged(int position)
{
	printf("Slider position: %d\n", position);
}
