#include "lib-api.h"
#include "lib-errors.h"
#include "lib-main.h"

namespace TrkSim {

///////////////////////////////////////////////////////////////////////////////

void callEv(void *sender, const LibStdCallback &callback) {
	if (nullptr != callback.func)
		callback.func(sender, callback.data);
}

///////////////////////////////////////////////////////////////////////////////
// API

bool apiSupportsVersion(unsigned int version) {
	return std::find(API_SUPPORTED_VERSIONS.begin(), API_SUPPORTED_VERSIONS.end(), version) !=
	       API_SUPPORTED_VERSIONS.end();
}

int apiSetVersion(unsigned int version) {
	if (!apiSupportsVersion(version))
		return TRK_UNSUPPORTED_API_VERSION;

	lib.api_version = version;
	return 0;
}

unsigned int features() {
	return 0; // no features yet
}

///////////////////////////////////////////////////////////////////////////////
// Connect / disconnect

int connect() {
	if (lib.connected)
		return TRK_ALREADY_OPENNED;

	lib.log("Connecting...", LogLevel::Info);
	lib.events.call(lib.events.beforeOpen);

	lib.hist.push([]() {
		lib.log("Connected", LogLevel::Info);
		lib.connected = true;
		lib.events.call(lib.events.afterOpen);
		lib.events.call(lib.events.onTrkStatusChanged, lib.trkStatus);
	});

	return 0;
}

int disconnect() {
	lib.events.call(lib.events.beforeClose);

	if (!lib.connected)
		return TRK_NOT_OPENED;

	lib.log("Disconnecting...", LogLevel::Info);
	lib.hist.push([]() {
		lib.log("Disconnected", LogLevel::Info);
		lib.connected = false;
		lib.events.call(lib.events.afterClose);
	});

	return 0;
}

bool connected() { return lib.connected; }

///////////////////////////////////////////////////////////////////////////////

int trackStatus() { return static_cast<int>(lib.trkStatus); }

void setTrackStatus(unsigned int trkStatus, LibStdCallback ok, LibStdCallback) {
	auto status = static_cast<TrkStatus>(trkStatus);
	lib.log("PUT: Set track status: " + LibMain::trkStatusToString(status), LogLevel::Commands);
	lib.hist.push([status, ok]() {
		lib.log("GET: Track Status: " + LibMain::trkStatusToString(status), LogLevel::Commands);
		lib.trkStatus = status;
		callEv(&lib, ok);
		lib.events.call(lib.events.onTrkStatusChanged, lib.trkStatus);
	});
}

///////////////////////////////////////////////////////////////////////////////

void emergencyStop(LibStdCallback ok, LibStdCallback) {
	lib.log("PUT: Emergency Stop", LogLevel::Commands);
	lib.hist.push([ok]() {
		lib.log("GET: OK", LogLevel::Commands);
		callEv(&lib, ok);
	});
}

void locoEmergencyStop(uint16_t addr, LibStdCallback ok, LibStdCallback) {
	lib.log("PUT: Loco " + QString::number(addr) + " Emergency Stop", LogLevel::Commands);
	lib.hist.push([ok]() {
		lib.log("GET: OK", LogLevel::Commands);
		callEv(&lib, ok);
	});
}

void locoSetSpeed(uint16_t addr, int speed, bool dir, LibStdCallback ok, LibStdCallback) {
	lib.log("PUT: Loco " + QString::number(addr) + " set speed: " + QString::number(speed) +
	            ", direction: " + QString::number(static_cast<int>(dir)),
	        LogLevel::Commands);
	lib.hist.push([ok]() {
		lib.log("GET: OK", LogLevel::Commands);
		callEv(&lib, ok);
	});
}

void locoSetFunc(uint16_t addr, uint32_t funcMask, uint32_t funcState, LibStdCallback ok,
                 LibStdCallback) {
	lib.log("PUT: Loco " + QString::number(addr) + " set func: mask=" +
	            QString::number(funcMask, 2) + ", state=" + QString::number(funcState, 2),
	        LogLevel::Commands);
	lib.hist.push([ok]() {
		lib.log("GET: OK", LogLevel::Commands);
		callEv(&lib, ok);
	});
}

void locoAcquire(uint16_t addr, TrkAcquiredCallback acquired, LibStdCallback) {
	lib.log("PUT: Loco " + QString::number(addr) + " Acquire", LogLevel::Commands);
	lib.hist.push([addr, acquired]() {
		LocoInfo info;
		info.addr = addr;
		lib.log("GET: Loco Info", LogLevel::Commands);
		if (nullptr != acquired)
			acquired(&lib, info);
	});
}

void locoRelease(uint16_t addr, LibStdCallback ok) {
	lib.log("PUT: Loco " + QString::number(addr) + " Release", LogLevel::Commands);
	callEv(&lib, ok);
}

void pomWriteCv(uint16_t addr, uint16_t cv, uint8_t value, LibStdCallback ok, LibStdCallback) {
	lib.log("PUT: Loco " + QString::number(addr) + " POM CV " + QString::number(cv) +
	            ", val=" + QString::number(value),
	        LogLevel::Commands);
	lib.hist.push([ok]() {
		lib.log("GET: OK", LogLevel::Commands);
		callEv(&lib, ok);
	});
}

///////////////////////////////////////////////////////////////////////////////
// Event binders

void bindBeforeOpen(TrkStdNotifyEvent f, void *data) {
	lib.events.bind(lib.events.beforeOpen, f, data);
}

void bindAfterOpen(TrkStdNotifyEvent f, void *data) {
	lib.events.bind(lib.events.afterOpen, f, data);
}

void bindBeforeClose(TrkStdNotifyEvent f, void *data) {
	lib.events.bind(lib.events.beforeClose, f, data);
}

void bindAfterClose(TrkStdNotifyEvent f, void *data) {
	lib.events.bind(lib.events.afterClose, f, data);
}

void bindOnTrackStatusChange(TrkStatusChangedEv f, void *data) {
	lib.events.bind(lib.events.onTrkStatusChanged, f, data);
}

void bindOnLog(TrkLogEv f, void *data) {
	lib.events.bind(lib.events.onLog, f, data);
}

void bindOnLocoStolen(TrkLocoEv f, void *data) {
	lib.events.bind(lib.events.onLocoStolen, f, data);
}

///////////////////////////////////////////////////////////////////////////////

} // namespace TrkSim
