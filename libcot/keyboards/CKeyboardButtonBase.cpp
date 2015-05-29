#include "CKeyboardButtonBase.h"

CKeyboardButtonBase::CKeyboardButtonBase(QWidget *parent)
    : QPushButton(parent)
{
    setAutoDefault( false );
    setMinimumSize( QSize( 41, 22 ) );
}

CKeyboardButtonBase::~CKeyboardButtonBase()
{

}

