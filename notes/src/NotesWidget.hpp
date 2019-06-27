#ifndef __NOTES_HPP__
#define __NOTES_HPP__

//-----------------------------------------------------------------------------

#include <QtWidgets/QWidget>

#include "Notes_ui.hpp"

//-----------------------------------------------------------------------------

class NotesWidget : public QWidget
{
	Q_OBJECT

public:
	NotesWidget(QWidget * parent = nullptr);

private:
	Ui::Notes_ui m_ui;
};

//-----------------------------------------------------------------------------

#endif // __NOTES_HPP__
