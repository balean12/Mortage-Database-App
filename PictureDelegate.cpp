#include "PictureDelegate.h"
#include <qpixmap.h>
#include <qpainter.h>

PictureDelegate::PictureDelegate(QWidget* parent) : QStyledItemDelegate{ parent }
{
}
void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() != 3)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	if (index.row() % 2 == 0)
	{
		QPixmap pixMap("male.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else {
		QPixmap pixMap("female.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{

	// show a picture only in the second column; the other columns remain unchanged
	if (index.column() == 3)
	{
		return QSize(80, 150);
	}

	return QStyledItemDelegate::sizeHint(option, index);
}
