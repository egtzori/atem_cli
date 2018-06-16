#ifndef APP_H
#define APP_H

#include <QCoreApplication>
#include <QTimer>


#include "qatemconnection.h"
#include "qatemmixeffect.h"
#include "qatemdownstreamkey.h"


#define NUM_CHANNELS 8 /* HARD */
#define CONN_TIMEOUT_MS 1000

class App: public QCoreApplication {
    Q_OBJECT

    public:
        App(int argc, char* argv[]);
        QAtemConnection *m_atemConnection;

    private:
        char **argv;
        int argc;
        QTimer* mTimer;

    protected slots:
        void onAtemConnected();
        void on_connection_timeout();
};


#endif // APP_H
