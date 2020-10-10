#include "./ui_cgol.h"
#include <QtWidgets/QPushButton>
#include <utility>

#include "cgol_window.hpp"

CGOLWindow::CGOLWindow(std::shared_ptr<CGOLBoard> board, QWidget *parent)
	: QWidget{parent},
	  ui_{std::make_unique<Ui::CGOLWindow>()},
	  cgol_board_{std::move(board)},
	  cgol_frame_{std::make_unique<CGOLFrame>(cgol_board_, this)}
{
	ui_->setupUi(this);
	ui_->verticalLayout->addWidget(cgol_frame_.get());
	connect(ui_->boardSizeSlider,
			&QSlider::valueChanged,
			cgol_frame_.get(),
			&CGOLFrame::sizeSliderValueChangedCallback);
	ui_->boardSizeSlider->setRange(20, 200);
	ui_->boardSizeSlider->setValue(50);
	connect(ui_->startButton, &QPushButton::clicked, cgol_frame_.get(), &CGOLFrame::start);
	connect(ui_->speedSlider, &QSlider::valueChanged, cgol_frame_.get(), &CGOLFrame::speedSliderValueChangedCallback);
	ui_->speedSlider->setValue(10);
	ui_->speedSlider->setRange(1, 300);
}

CGOLWindow::~CGOLWindow() = default;
