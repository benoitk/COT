#ifndef ICONFIGURATOREDITWINDOW_H
#define ICONFIGURATOREDITWINDOW_H

#include <QWidget>
#include <QVariant>

namespace Ui {
class IConfiguratorEditWindow;
}

class IConfiguratorEditTab;

/*
 * This is tha base window to use when creating an object edit window.
 * You insert in IConfiguratorEditTab tabs.
 * You must call initBaseWindow() as the last member in your constructor.
 * You call applyProperties() when validating your window.
 */
class IConfiguratorEditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit IConfiguratorEditWindow(const QVariant &object, QWidget *parent = Q_NULLPTR);
    virtual ~IConfiguratorEditWindow();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

    QVariant editedObject() const;
    void initBaseWindow();
    void addTab(IConfiguratorEditTab *tab);
    void setTabText(int index, const QString &text);
    virtual void applyProperties();

private slots:
    virtual void slotRetranslate() = 0;
    virtual void slotOkTriggered() = 0;
    virtual void slotCancelTriggered() = 0;

private:
    Ui::IConfiguratorEditWindow *ui;
    QVariant m_editedObject;
};

#endif // ICONFIGURATOREDITWINDOW_H
