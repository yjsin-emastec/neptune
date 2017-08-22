#-----------------------------------------------------------------------------
# 4CH CDVR (1080p)
#-----------------------------------------------------------------------------

#1-ntsc, 0-pal
CDVR_VIS?=1

CDVR_VIDEO?=4
CDVR_AUDIO?=4

# 0,..,16 - num of trigger
CDVR_TRIGGER_OUT?=1

# 0,..,16 - num of sensor
CDVR_TRIGGER_IN?=4

CDVR_HDD?=1

CDVR_MA?=1

CDVR_MODEL?=1

# 0 - HD
# 1 - AD
# 2 - SD
CDVR_VODEV?=0

# 0 (VGA)
# 1 (HDMI)
CDVR_VO_HDMI?=1

# 0  (800  * 600  * 60p)
# 1  (1024 * 768  * 60p)
# 2  (1280 * 1024 * 60p)
# 3  (1366 * 768  * 60p)
# 4  (1440 * 900  * 60p)
# 5  (800  * 600  * 75)
# 6  (1024 * 768  * 75)
# 7  (HD 720  * 60p)
# 8  (HD 1080 * 50i)
# 9  (HD 1080 * 60i)
# 10 (HD 1080 * 25p)
# 11 (HD 1080 * 30p)
CDVR_DISP_RESOLUTION?=9

# 0 - SOFTWARE
# 1 - HARDWARE
CDVR_MOUSE_CURSOR?=0

# 0 - EASTERN
CDVR_OEM?=$(EA_OEM)

# 0 - none
CDVR_SUB_MODEL?=$(EA_SUB_MODEL)

CDVR_REF_YEAR?=$(EA_REF_YEAR)

# 0 - Korea
# 1 - Europe
# 2 - North America
# 3 - Japan
CDVR_REGION?=$(EA_REGION)

CDVRFLAGS += -DCDVR_VIS=$(CDVR_VIS)
CDVRFLAGS += -DCDVR_VIDEO=$(CDVR_VIDEO)
CDVRFLAGS += -DCDVR_AUDIO=$(CDVR_AUDIO)
CDVRFLAGS += -DCDVR_TRIGGER_OUT=$(CDVR_TRIGGER_OUT)
CDVRFLAGS += -DCDVR_TRIGGER_IN=$(CDVR_TRIGGER_IN)
CDVRFLAGS += -DCDVR_HDD=$(CDVR_HDD)
CDVRFLAGS += -DCDVR_MODEL=$(CDVR_MODEL)
CDVRFLAGS += -DCDVR_VODEV=$(CDVR_VODEV)
CDVRFLAGS += -DCDVR_MA=$(CDVR_MA)
CDVRFLAGS += -DCDVR_VO_HDMI=$(CDVR_VO_HDMI)
CDVRFLAGS += -DCDVR_DISP_RESOLUTION=$(CDVR_DISP_RESOLUTION)
CDVRFLAGS += -DCDVR_MOUSE_CURSOR=$(CDVR_MOUSE_CURSOR)
CDVRFLAGS += -DCDVR_OEM=$(CDVR_OEM)
CDVRFLAGS += -DCDVR_SUB_MODEL=$(CDVR_SUB_MODEL)
CDVRFLAGS += -DCDVR_REF_YEAR=$(CDVR_REF_YEAR)
CDVRFLAGS += -DCDVR_REGION=$(CDVR_REGION)
