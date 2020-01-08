#ifndef LIBAPI_H
#define LIBAPI_H

#include <array>

#include "lib-api-common-def.h"
#include "lib-events.h"

namespace TrkSim {

constexpr std::array<unsigned int, 1> API_SUPPORTED_VERSIONS {
    0x0001, // v1.0
};

extern "C" {

using LibCallbackFunc = void CALL_CONV (*)(void *sender, void *data);

struct LibStdCallback {
	LibCallbackFunc func;
	void *const data;
};

struct LocoInfo {
	uint16_t addr = 0;
	bool direction = false;
	uint8_t speed = 0;
	uint8_t maxSpeed = 28;
	uint32_t functions = 0;
	bool usedByAnother = false;
};

using TrkAcquiredCallback = void CALL_CONV (*)(const void *sender, LocoInfo);

SIM_SHARED_EXPORT bool CALL_CONV apiSupportsVersion(unsigned int version);
SIM_SHARED_EXPORT int CALL_CONV apiSetVersion(unsigned int version);
SIM_SHARED_EXPORT unsigned int CALL_CONV features();

SIM_SHARED_EXPORT int CALL_CONV loadConfig(char16_t *filename);
SIM_SHARED_EXPORT int CALL_CONV saveConfig(char16_t *filename);

SIM_SHARED_EXPORT int CALL_CONV connect();
SIM_SHARED_EXPORT int CALL_CONV disconnect();
SIM_SHARED_EXPORT bool CALL_CONV connected();

SIM_SHARED_EXPORT int CALL_CONV trackStatus();
SIM_SHARED_EXPORT void CALL_CONV setTrackStatus(unsigned int trkStatus, LibStdCallback ok,
                                                LibStdCallback err);

SIM_SHARED_EXPORT void CALL_CONV emergencyStop(LibStdCallback ok, LibStdCallback err);
SIM_SHARED_EXPORT void CALL_CONV locoEmergencyStop(uint16_t addr, LibStdCallback ok,
                                                   LibStdCallback err);
SIM_SHARED_EXPORT void CALL_CONV locoSetSpeed(uint16_t addr, int speed, bool dir, LibStdCallback ok,
                                              LibStdCallback err);
SIM_SHARED_EXPORT void CALL_CONV locoSetFunc(uint16_t addr, uint32_t funcMask, uint32_t funcState,
                                             LibStdCallback ok, LibStdCallback err);
SIM_SHARED_EXPORT void CALL_CONV locoAcquire(uint16_t addr, TrkAcquiredCallback,
                                             LibStdCallback err);
SIM_SHARED_EXPORT void CALL_CONV locoRelease(uint16_t addr, LibStdCallback ok);

SIM_SHARED_EXPORT void CALL_CONV pomWriteCv(uint16_t addr, uint16_t cv, uint8_t value,
                                            LibStdCallback ok, LibStdCallback err);

SIM_SHARED_EXPORT void CALL_CONV bindBeforeOpen(TrkStdNotifyEvent f, void *data);
SIM_SHARED_EXPORT void CALL_CONV bindAfterOpen(TrkStdNotifyEvent f, void *data);
SIM_SHARED_EXPORT void CALL_CONV bindBeforeClose(TrkStdNotifyEvent f, void *data);
SIM_SHARED_EXPORT void CALL_CONV bindAfterClose(TrkStdNotifyEvent f, void *data);
SIM_SHARED_EXPORT void CALL_CONV bindOnTrackStatusChange(TrkStatusChangedEv f, void *data);
SIM_SHARED_EXPORT void CALL_CONV bindOnLog(TrkLogEv f, void *data);
SIM_SHARED_EXPORT void CALL_CONV bindOnLocoStolen(TrkLocoEv f, void *data);
}

} // namespace TrkSim

#endif
