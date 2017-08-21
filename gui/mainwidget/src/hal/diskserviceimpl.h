#ifndef DISKSERVICEIMPL_H
#define DISKSERVICEIMPL_H

#include "diskservice.h"
#include "appmgr.h"
#include "testmgr.h"

class AppmgrDiskService : public DiskService
{
public:
    virtual int  diskState()                      { return appmgr_get_boot_disk_state();    }
    virtual void diskInfo(disk_used_info_t *info) { appmgr_get_disk_info(info);             }
    virtual void format(int diskNumber)           { appmgr_disk_format(diskNumber);         }
    virtual int  formatResult()                   { return appmgr_get_format_result();      }
};

class TestmgrDiskService : public DiskService
{
public:
    virtual int  diskState()                      { return testmgr_get_boot_format_state(); }
    virtual void diskInfo(disk_used_info_t *info) { ;                                       }
    virtual void format(int diskNumber)           { testmgr_disk_format(diskNumber);        }
    virtual int  formatResult()                   { return testmgr_get_format_result();     }
};

#endif
