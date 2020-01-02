#ifndef LIB_COMMON_DEF_H
#define LIB_COMMON_DEF_H

namespace TrkSim {

enum class LogLevel {
	None = 0,
	Error = 1,
	Warning = 2,
	Info = 3,
	Commands = 4,
	RawData = 5,
	Debug = 6,
};

enum class TrkStatus {
	Unknown = 0,
	Off = 1,
	On = 2,
	Programming = 3,
};

} // namespace TrkSim

#endif
