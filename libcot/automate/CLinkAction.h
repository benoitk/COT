#ifndef CLINKACTION_H
#define CLINKACTION_H

#include <QObject>

class IAction;
class CLinkAction : public QObject
{
    Q_OBJECT

public:
    CLinkAction(int, IAction*);
    ~CLinkAction();

    int getNum()const;
    IAction* getAction()const;

private:
    IAction* m_action;
};

#endif // CLINKACTION_H
