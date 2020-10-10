#include "cgol_window.hpp"
#include "./ui_cgol.h"

CGOLWindow::CGOLWindow(QWidget *parent)
	: QWidget{parent},
	  ui{new Ui::CGOLWindow},
	  cgol_board_{new CGOLBoard(this)}
{
	ui->setupUi(this);
	ui->verticalLayout->addWidget(cgol_board_);
	connect(ui->startButton, &QPushButton::clicked, cgol_board_, &CGOLBoard::start);
	connect(ui->speedSlider, &QSlider::valueChanged, cgol_board_, &CGOLBoard::setSpeed);
	ui->speedSlider->setValue(10);
	ui->speedSlider->setRange(1, 200);
	connect(ui->boardSizeSlider, &QSlider::valueChanged, cgol_board_, &CGOLBoard::setSize);
	ui->boardSizeSlider->setRange(20, 200);
	ui->boardSizeSlider->setValue(50);
}

CGOLWindow::~CGOLWindow()
{
	delete ui;
}
