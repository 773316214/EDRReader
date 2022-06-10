#ifndef BAR_H
#define BAR_H

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

class Bar
{
public:
    Bar();

    QMenuBar SetMenubar();
    QToolBar SetToolbar();
    QStatusBar SetStatusbar();
private:
    QMenuBar *menubar_{nullptr};
    QToolBar *toolbar_{nullptr};
    QStatusBar *statusbar_{nullptr};
};

#endif // BAR_H
