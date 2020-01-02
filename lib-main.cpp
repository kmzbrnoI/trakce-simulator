#include "lib-main.h"

namespace TrkSim {

AppThread main_thread;
LibMain lib;

LibMain::LibMain() {
	QObject::connect(&m_hist_timer, SIGNAL(timeout()), this, SLOT(m_hist_timer_tick()));
	m_hist_timer.start(100);
	log("Library loaded.", LogLevel::Info);
}

void LibMain::log(const QString &msg, LogLevel loglevel) const {
	events.call(events.onLog, loglevel, msg);
}

void LibMain::m_hist_timer_tick() {
	if (!hist.empty()) {
		hist.front()();
		hist.pop();
	}
}

QString LibMain::trkStatusToString(const TrkStatus ts) {
	if (ts == TrkStatus::Off)
		return "Off";
	else if (ts == TrkStatus::On)
		return "On";
	else if (ts == TrkStatus::Programming)
		return "Programming";
	else
		return "Unknown";
}

} // namespace TrkSim
