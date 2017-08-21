#!/bin/sh

#VICAP
#XD1
himm 0x2003002c 0xf0f00000  # no reset
himm 0x20030030 0xe4255000  # 16xD1  MUX4
#4X720P
#himm 0x2003002c 0xf0f00000  # no reset
#himm 0x20030030 0xe4200000  # 4x720P MUX2
#2X1080P
#himm 0x2003002c 0xf0f00000  # no reset
#himm 0x20030030 0xe42aa000  # 2x1080P MUX1
#1HD+7XD1
#himm 0x2003002c 0xf0f00000  # no reset
#himm 0x20030030 0xe42a5000  # 1HD+7xD1 MUX1

#VO
himm 0x20030034 0x6f30       # VO crg
himm 0x2003003c 0xc          # HDMI need confirm

himm 0x20030040 0x802   #VEDU & SED
himm 0x20030048 0x2     #VPSS
himm 0x20030050 0x2     #VDH
himm 0x200300d4 0x8     #SCD 
himm 0x20030058 0x2     #TDE
himm 0x20030060 0x2     #JPGE
himm 0x20030064 0x2     #JPGD
himm 0x20030068 0x2     #MD
himm 0x2003006c 0x2     #IVE/VAPU
himm 0x20030070 0x2     #VOIE/AENC
himm 0x20030074 0x2     #VCMP
himm 0x2003007c 0x2     #CIPHER 
himm 0x200300e0 0x2     #DMA 

#SIOx(x=0~3)
himm 0x20030080 0x00218def   #SIO0/1/Mclk  crg32  ����
himm 0x20030084 0x00218def   #SIO2   mclk  crg33  ���롢���
himm 0x20030088 0x00218def   #SIO3   mclk  crg34  ���
himm 0x2003008c 0x000015c2   #SIO0  ʱ�Ӹ�λ��Ƶcrg35 ����
himm 0x20030090 0x000015c2   #SIO1  ʱ�Ӹ�λ��Ƶcrg36 ����
himm 0x20030094 0x000015d2   #SIO2  ʱ�Ӹ�λ��Ƶcrg37 ���롢���
himm 0x20030098 0x000015d2   #SIO3  ʱ�Ӹ�λ��Ƶcrg38 ���