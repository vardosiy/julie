#ifndef __NOTES_HPP__
#define __NOTES_HPP__

//-----------------------------------------------------------------------------

#include <QtWidgets/QWidget>

#include "Ui_NotesWidget.hpp"

//-----------------------------------------------------------------------------

class NotesWidget : public QWidget
{
	Q_OBJECT

public:
	NotesWidget(QWidget * _parent = nullptr);

private:
	Ui::NotesWidget m_ui;
};

//-----------------------------------------------------------------------------

#endif // __NOTES_HPP__
