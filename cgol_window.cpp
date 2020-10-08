#include "cgol_window.hpp"
#include "./ui_cgol.h"

CGOLWindow::CGOLWindow(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::CGOLWindow),
	  cgol_board_(new CGOLBoard(this))
{
	ui->setupUi(this);
	ui->verticalLayout->addWidget(cgol_board_);
	connect(ui->startButton, &QPushButton::clicked, cgol_board_, &CGOLBoard::start);
	connect(ui->speedSlider, &QSlider::valueChanged, cgol_board_, &CGOLBoard::setSpeed);
}

CGOLWindow::~CGOLWindow()
{
	delete ui;
}
