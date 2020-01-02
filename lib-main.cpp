#include "lib-main.h"

namespace TrkSim {

AppThread main_thread;
LibMain lib;

LibMain::LibMain() {
	QObject::connect(&m_hist_timer, SIGNAL(timeout()), this, SLOT(m_hist_timer_tick()));
	m_hist_timer.start(100);
	log("Library loaded.", LogLevel::Info);
}

void LibMain::log(const QString &msg, LogLevel loglevel) {
	events.call(events.onLog, loglevel, msg);
}

void LibMain::m_hist_timer_tick() {}

} // namespace Xn
