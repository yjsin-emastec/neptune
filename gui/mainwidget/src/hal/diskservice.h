#ifndef DISKSERVICE_H
#define DISKSERVICE_H

#include <DVR.h>
#include "halservice.h"

// Disk information & service.
class DiskService : public HALService<DiskService>
{
public:
	virtual int diskState()                       = 0; // Get disk state.
	virtual void diskInfo(disk_used_info_t *info) = 0; // Get disk information.
	virtual void format(int diskNumber)           = 0; // Format disk.
	virtual int formatResult()                    = 0; // Get format result.
};

#endif
