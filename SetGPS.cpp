#include <stm32f30x.h>
#include <string.h>

enum GPSCommand
{
	PMTK_TEST = 000,
	PMTK_ACK = 001,
	PMTK_SYS_MSG = 010,
	PMTK_TXT_MSG = 011,
	PMTK_CMD_HOT_START = 101,
	PMTK_CMD_WARM_START = 102,
	PMTK_CMD_COLD_START = 103,
	PMTK_CMD_FULL_COLD_START = 104,
	PMTK_SET_NMEA_UPDATERATE = 220,
	PMTK_SET_NMEA_BAUDRATE = 251,
	PMTK_API_SET_DGPS_MODE = 301,
	PMTK_API_Q_DGPS_MODE = 401,
	PMTK_API_DT_DGPS_MODE = 501,
	PMTK_API_SET_SBAS_ENABLED = 313,
	PMTK_API_Q_SBAS_ENABLED = 413,
	PMTK_DT_SBAS_ENABLED = 513,
	PMTK_API_SET_NMEA_OUTPUT = 314,
	PMTK_API_Q_NMEA_OUTPUT = 414,
	PMTK_API_DT_NMEA_OUTPUT = 514,
	PMTK_API_SET_SBAS_Mode = 319,
	PMTK_API_Q_SBAS_Mode = 419,
	PMTK_API_DT_SBAS_Mode = 519,
	PMTK_Q_RELEASE = 605,
	PMTK_DT_RELEASE = 705,
	PMTK_Q_EPO_INFO = 607,
	PMTK_DT_EPO_INFO = 707,
	PMTK_CMD_CLEAR_EPO = 127,
	PMTK_SET_Nav = 386,
	PMTK_Q_Nav_Threshold = 447,
	PMTK_DT_Nav_Threshold = 527,
	PMTK_CMD_STANDBY_MODE = 161,
	PMTK_SET_AL_DEE_CFG = 223,
	PMTK_CMD_PERIODIC_MODE = 225,
	PMTK_CMD_AIC_MODE = 286,
	PMTK_CMD_EASY_ENABLE = 869,
	PMTK_LOCUS_CONFIG = 187,
	PMTK_API_SET_DATUM = 330,
	PMTK_API_Q_DATUM = 430,
	PMTK_API_DT_DATUM = 530,
	PMTK_API_SET_SUPPORT_QZSS_NMEA = 351,
	PMTK_API_SET_STOP_QZSS = 352
};

void sendGPSCommand(GPSCommand command)
{
	char gpscommand[50];
	switch (command)
	{
	case PMTK_TEST:
		strcpy(gpscommand, "$PMTK000*32");
		break;
	case PMTK_ACK:
		strcpy(gpscommand, "");
		break;
	case PMTK_SYS_MSG:
		strcpy(gpscommand, "$PMTK010,001*2E");
		break;
	case PMTK_TXT_MSG:
		strcpy(gpscommand, "$PMTK011,MTKGPS*08");
		break;
	case PMTK_CMD_HOT_START:
		strcpy(gpscommand, "$PMTK101*32");
		break;
	case PMTK_CMD_WARM_START:
		strcpy(gpscommand, "$PMTK102*31");
		break;
	case PMTK_CMD_COLD_START:
		strcpy(gpscommand, "$PMTK103*30");
		break;
	case PMTK_CMD_FULL_COLD_START:
		strcpy(gpscommand, "$PMTK104*37");
		break;
	case PMTK_SET_NMEA_UPDATERATE:
		strcpy(gpscommand, "$PMTK220,100*2F");
		break;
	case PMTK_SET_NMEA_BAUDRATE:
		strcpy(gpscommand, "$PMTK251,38400*27");
		break;
	case PMTK_API_SET_DGPS_MODE:
		strcpy(gpscommand, "$PMTK301,1*2D");
		break;
	case PMTK_API_Q_DGPS_MODE:
		strcpy(gpscommand, "$PMTK401*37");
		break;
	case PMTK_API_DT_DGPS_MODE:
		strcpy(gpscommand, "$PMTK501,2*28");
		break;
	case PMTK_API_SET_SBAS_ENABLED:
		strcpy(gpscommand, "$PMTK313,1*2E");
		break;
	case PMTK_API_Q_SBAS_ENABLED:
		strcpy(gpscommand, "$PMTK413*34");
		break;
	case PMTK_DT_SBAS_ENABLED:
		strcpy(gpscommand, "$PMTK513,1*28");
		break;
	case PMTK_API_SET_NMEA_OUTPUT:
		strcpy(gpscommand, "");
		break;
	case PMTK_API_Q_NMEA_OUTPUT:
		strcpy(gpscommand, "$PMTK414*33");
		break;
	case PMTK_API_DT_NMEA_OUTPUT:
		strcpy(gpscommand, "");
		break;
	case PMTK_API_SET_SBAS_Mode:
		strcpy(gpscommand, "$PMTK319,1*24");
		break;
	case PMTK_API_Q_SBAS_Mode:
		strcpy(gpscommand, "$PMTK419*3E");
		break;
	case PMTK_API_DT_SBAS_Mode:
		strcpy(gpscommand, "$PMTK519,1*22");
		break;
	case PMTK_Q_RELEASE:
		strcpy(gpscommand, "$PMTK605*31");
		break;
	case PMTK_DT_RELEASE:
		strcpy(gpscommand, "");
		break;
	case PMTK_Q_EPO_INFO:
		strcpy(gpscommand, "$PMTK607*33");
		break;
	case PMTK_DT_EPO_INFO:
		strcpy(gpscommand, "");
		break;
	case PMTK_CMD_CLEAR_EPO:
		strcpy(gpscommand, "$PMTK127*36");
		break;
	case PMTK_SET_Nav:
		strcpy(gpscommand, "");
		break;
	case PMTK_Q_Nav_Threshold:
		strcpy(gpscommand, "$PMTK447*35");
		break;
	case PMTK_DT_Nav_Threshold:
		strcpy(gpscommand, "");
		break;
	case PMTK_CMD_STANDBY_MODE:
		strcpy(gpscommand, "$PMTK161,0*28");
		break;
	case PMTK_SET_AL_DEE_CFG:
		strcpy(gpscommand, "");
		break;
	case PMTK_CMD_PERIODIC_MODE:
		strcpy(gpscommand, "");
		break;
	case PMTK_CMD_AIC_MODE:
		strcpy(gpscommand, "$PMTK286,1*23");
		break;
	case PMTK_CMD_EASY_ENABLE:
		strcpy(gpscommand, "$PMTK869,2,0*37");
		break;
	case PMTK_LOCUS_CONFIG:
		strcpy(gpscommand, "$PMTK187,1,5*38");
		break;
	case PMTK_API_SET_DATUM:
		strcpy(gpscommand, "$PMTK330,0*2E");
		break;
	case PMTK_API_Q_DATUM:
		strcpy(gpscommand, "$PMTK430*35");
		break;
	case PMTK_API_DT_DATUM:
		strcpy(gpscommand, "$PMTK530,0*28");
		break;
	case PMTK_API_SET_SUPPORT_QZSS_NMEA:
		strcpy(gpscommand, "$PMTK351,1*28");
		break;
	case PMTK_API_SET_STOP_QZSS:
		strcpy(gpscommand, "$PMTK352,1*2A");
		break;
	default:
		break;
	}
}
