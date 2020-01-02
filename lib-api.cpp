#include "lib-api.h"
#include "lib-main.h"
#include "lib-errors.h"

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

	lib.events.call(lib.events.beforeOpen);


	return 0;
}

int disconnect() {
	lib.events.call(lib.events.beforeClose);

	if (!lib.connected)
		return TRK_NOT_OPENED;


	return 0;
}

bool connected() {
	return lib.connected;
}

///////////////////////////////////////////////////////////////////////////////

int trackStatus() {
	return static_cast<int>(lib.trkStatus);
}

void setTrackStatus(unsigned int trkStatus, LibStdCallback ok, LibStdCallback err) {
}

///////////////////////////////////////////////////////////////////////////////

void emergencyStop(LibStdCallback ok, LibStdCallback err) {
}

void locoEmergencyStop(uint16_t addr, LibStdCallback ok, LibStdCallback err) {
}

void locoSetSpeed(uint16_t addr, int speed, bool dir, LibStdCallback ok, LibStdCallback err) {
}

void locoSetFunc(uint16_t addr, uint32_t funcMask, uint32_t funcState, LibStdCallback ok,
                 LibStdCallback err) {
}

void locoAcquire(uint16_t addr, TrkAcquiredCallback acquired, LibStdCallback err) {
}

void locoRelease(uint16_t addr, LibStdCallback ok) {
	(void)addr;
	callEv(&lib, ok);
}

void pomWriteCv(uint16_t addr, uint16_t cv, uint8_t value, LibStdCallback ok, LibStdCallback err) {
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
