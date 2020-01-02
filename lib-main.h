#ifndef LIB_MAIN_H
#define LIB_MAIN_H

#include <deque>
#include <functional>
#include <memory>
#include <QCoreApplication>
#include <QTimer>

#include "lib-common-defs.h"
#include "lib-events.h"

namespace TrkSim {

///////////////////////////////////////////////////////////////////////////////

using HistoryFunc = std::function<void()>;

class LibMain : public QObject {
	Q_OBJECT
public:
	XnEvents events;
	unsigned int api_version = 0x0001;
	bool connected = false;
	QTimer m_hist_timer;
	std::deque<HistoryFunc> hist;
	TrkStatus trkStatus = TrkStatus::On;

	LibMain();

	void log(const QString &msg, LogLevel loglevel);

private slots:
	void m_hist_timer_tick();

private:

};

///////////////////////////////////////////////////////////////////////////////

// Dirty magic for Qt's event loop
// This class should be created first
class AppThread {
	std::unique_ptr<QCoreApplication> app;
	int argc {0};

public:
	AppThread() {
		app = std::make_unique<QCoreApplication>(argc, nullptr);
		QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
		app->exec();
	}
};

extern AppThread main_thread;
extern LibMain lib;

} // namespace TrkSim

#endif
