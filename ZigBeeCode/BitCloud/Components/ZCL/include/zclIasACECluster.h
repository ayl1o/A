/*****************************************************************************
  \file  zclIasZoneCluster.h

  \brief
    The file describes the types and interface of the
    Relative Humidity Measurement cluster.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    18.11.14 Yogesh Bellan - Created.
******************************************************************************/


#ifndef _ZCLIASACECLUSTER_H_
#define _ZCLIASACECLUSTER_H_

/*******************************************************************************
                   Includes section
*******************************************************************************/
#include <sysTypes.h>
#include <zclIasZoneCluster.h>
#include <clusters.h>

/*******************************************************************************
                   Define(s) section
*******************************************************************************/
/**
 * \brief Request commands
*/


#define ZCL_IAS_ACE_CLUSTER_ARM_COMMAND_ID                                      0x00
#define ZCL_IAS_ACE_CLUSTER_BYPASS_COMMAND_ID                                   0x01
#define ZCL_IAS_ACE_CLUSTER_EMERGENCY_COMMAND_ID                                0x02
#define ZCL_IAS_ACE_CLUSTER_FIRE_COMMAND_ID                                     0x03
#define ZCL_IAS_ACE_CLUSTER_PANIC_COMMAND_ID                                    0x04
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_COMMAND_ID                          0x05
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_COMMAND_ID                     0x06
#define ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_COMMAND_ID                         0x07
#define ZCL_IAS_ACE_CLUSTER_GET_BYPASSED_ZONE_LIST_COMMAND_ID                   0x08
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_COMMAND_ID                          0x09

/**
 * \brief server response commands
*/
#define ZCL_IAS_ACE_CLUSTER_ARM_RESPONSE_COMMAND_ID                             0x00
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID                 0x01
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID            0x02
#define ZCL_IAS_ACE_CLUSTER_ZONE_STATUS_CHANGED_COMMAND_ID                      0x03
#define ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID                     0x04
#define ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_RESPONSE_COMMAND_ID                0x05
#define ZCL_IAS_ACE_CLUSTER_SET_BYPASSED_ZONE_LIST_COMMAND_ID                   0x06
#define ZCL_IAS_ACE_CLUSTER_BYPASS_RESPONSE_COMMAND_ID                          0x07
#define ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_RESPONSE_COMMAND_ID                 0x08

//Total of 19 Commands
#define ZCL_IAS_ACE_CLUSTER_COMMANDS_AMOUNT                                     0x13
#define ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE                                        0x08
#define ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE                                        0x10
#define ZCL_IAS_ACE_ZONE_LABEL_SIZE                                             0x02

/**
 * \brief cluster attributes amount
*/
#define ZCL_IAS_ACE_CLUSTER_ATTRIBUTES_AMOUNT                                   0x00

/**
 * \brief server response commands
*/
/***************************************************************************//**
\brief IAS Zone Cluster define commands macros
*******************************************************************************/
#define IAS_ACE_CLUSTER_ZCL_SERVER_CLUSTER_TYPE(clattributes, clcommands) \
  { \
    .id = IAS_ACE_CLUSTER_ID, \
    .options = {.type = ZCL_SERVER_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY}, \
    .attributesAmount = ZCL_IAS_ACE_CLUSTER_ATTRIBUTES_AMOUNT, \
    .attributes = clattributes, \
    .commandsAmount = ZCL_IAS_ACE_CLUSTER_COMMANDS_AMOUNT, \
    .commands = (uint8_t *)clcommands \
  }

#define IAS_ACE_CLUSTER_ZCL_CLIENT_CLUSTER_TYPE(clattributes, clcommands) \
  { \
    .id = IAS_ACE_CLUSTER_ID, \
    .options = {.type = ZCL_CLIENT_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY}, \
    .attributesAmount = ZCL_IAS_ACE_CLUSTER_ATTRIBUTES_AMOUNT, \
    .attributes = clattributes, \
    .commandsAmount = ZCL_IAS_ACE_CLUSTER_COMMANDS_AMOUNT, \
    .commands = (uint8_t *)clcommands \
  }

#define DEFINE_IAS_ACE_CLUSTER(cltype, clattributes, clcommands) \
    IAS_ACE_CLUSTER_##cltype(clattributes, clcommands)

/***************************************************************************//**
\brief IAS ACE Cluster define commands macros
*******************************************************************************/      
#define ZCL_DEFINE_IAS_ACE_CLUSTER_COMMANDS(aceArmCommandInd,\
                                            aceArmResponseCommandInd,\
                                            aceByPassCommandInd,\
                                            aceEmergencyCommandInd,\
                                            aceFireCommandInd,\
                                            acePanicCommandInd,\
                                            aceGetZoneIdMapCommandInd,\
                                            aceGetZoneIdMapResponseCommandInd,\
                                            aceGetZoneInformationCommandInd,\
                                            aceGetZoneInformationResponseCommandInd,\
                                            aceGetPanelStatusCommandInd,\
                                            aceGetPanelStatusCommandRespInd,\
                                            aceGetZoneStatusCommandInd,\
                                            aceGetZoneStatusRespCommandInd,\
                                            acePanelStatusChangedCommandInd,\
                                            aceZoneStatusChangedCommandInd,\
                                            aceGetByPassesZoneListCommandInd,\
                                            aceSetByPassesZoneListCommandInd,\
                                            aceByPassResponseCommandInd)\
    DEFINE_COMMAND(aceArmCommand, ZCL_IAS_ACE_CLUSTER_ARM_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceArmCommandInd),\
    DEFINE_COMMAND(aceArmResponseCommand, ZCL_IAS_ACE_CLUSTER_ARM_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     aceArmResponseCommandInd),\
    DEFINE_COMMAND(aceByPassCommand, ZCL_IAS_ACE_CLUSTER_BYPASS_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceByPassCommandInd),\
    DEFINE_COMMAND(aceEmergencyCommand, ZCL_IAS_ACE_CLUSTER_EMERGENCY_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceEmergencyCommandInd),\
    DEFINE_COMMAND(aceFireCommand, ZCL_IAS_ACE_CLUSTER_FIRE_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceFireCommandInd),\
    DEFINE_COMMAND(acePanicCommand, ZCL_IAS_ACE_CLUSTER_PANIC_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     acePanicCommandInd),\
    DEFINE_COMMAND(aceGetZoneIdMapCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneIdMapCommandInd),\
    DEFINE_COMMAND(aceGetZoneIdMapResponseCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_ID_MAP_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneIdMapResponseCommandInd),\
    DEFINE_COMMAND(aceGetZoneInformationCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneInformationCommandInd),\
    DEFINE_COMMAND(aceGetZoneInformationResponseCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_INFORMATION_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneInformationResponseCommandInd),\
    DEFINE_COMMAND(aceGetPanelStatusCommand, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetPanelStatusCommandInd),\
    DEFINE_COMMAND(aceGetPanelStatusCommandResp, ZCL_IAS_ACE_CLUSTER_GET_PANEL_STATUS_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetPanelStatusCommandRespInd),\
    DEFINE_COMMAND(aceGetZoneStatusCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneStatusCommandInd),\
    DEFINE_COMMAND(aceGetZoneStatusRespCommand, ZCL_IAS_ACE_CLUSTER_GET_ZONE_STATUS_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetZoneStatusRespCommandInd),\
    DEFINE_COMMAND(acePanelStatusChangedCommand, ZCL_IAS_ACE_CLUSTER_PANEL_STATUS_CHANGED_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     acePanelStatusChangedCommandInd),\
    DEFINE_COMMAND(aceZoneStatusChangedCommand, ZCL_IAS_ACE_CLUSTER_ZONE_STATUS_CHANGED_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceZoneStatusChangedCommandInd),\
    DEFINE_COMMAND(aceGetByPassedZoneListCommand, ZCL_IAS_ACE_CLUSTER_GET_BYPASSED_ZONE_LIST_COMMAND_ID,\
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceGetByPassesZoneListCommandInd),\
    DEFINE_COMMAND(aceSetByPassesZoneListCommand, ZCL_IAS_ACE_CLUSTER_SET_BYPASSED_ZONE_LIST_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceSetByPassesZoneListCommandInd),\
    DEFINE_COMMAND(aceByPassResponseCommand, ZCL_IAS_ACE_CLUSTER_BYPASS_RESPONSE_COMMAND_ID,\
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),\
                     aceByPassResponseCommandInd)
/******************************************************************************
                    Types section
******************************************************************************/
/**
 * \brief IAS Zone types
*/
typedef enum
{
  ALL_ZONE_DISARMED = 0X00,
  ONLY_DAY_HOME_ZONES_ARMED = 0X01,
  ONLY_NIGHT_SLEEP_ZONES_ARMED = 0X02,
  ALL_ZONE_ARMED  = 0X03,
  INVALID_ARMCODE = 0x04,
  NOT_READY_TO_ARM_STATE = 0x05,
  ALREADY_DISARMED = 0x06
} ZCL_ArmNotification_t;

typedef enum
{
  PANEL_DISARMED =0x00,
  ARMED_STAY = 0x01,
  ARMED_NIGHT = 0x02,
  ARMED_AWAY = 0x03,
  EXIT_DELAY = 0x04,
  ENTRY_DELAY = 0x05,
  NOT_READY_TO_ARM =0x06,
  IN_ALARM =0x07,
  ARMING_STAY = 0x08,
  ARMING_NIGHT = 0x09,
  ARMING_AWAY = 0x0A
}ZCL_PanelStatus_t;

typedef enum
{
  MUTE =0x00,
  DEFAULT_SOUND = 0x01
}ZCL_AudibleNotification_t;

typedef enum
{
  NO_ALARM =0x00,
  BURGLAR = 0x01,
  FIRE = 0X02,
  EMERGENCY = 0X03,
  POLICE_PANIC = 0X04,
  FIRE_PANIC = 0X05,
  EMERGENCY_PANIC = 0X06
}ZCL_AlarmStatus_t;
  
/**
 * \brief IAS ByPass Response
*/
typedef enum
{
  ZONE_BYPASSED = 0X00,
  ZONE_NOT_BYPASSED = 0X01,
  NOT_ALLOWED = 0X02,
  INVALID_ZONE_ID  = 0X03,
  UNKNOWN_ZONE_ID =0X04,
  INVALID_ARM_DISARM_CODE = 0X05
} ZCL_BypassRespType_t;

BEGIN_PACK

///**
// * \brief IAS Zone Cluster Commands/Structures.
//*/

//Arm Commands
typedef struct PACK
{
  ZCL_ArmNotification_t armMode;
  uint8_t lengthArmMode;
  char armDisarmCode[ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE];
  uint8_t zoneId;  
} ZCL_ACEArm_t;

typedef struct PACK
{
  ZCL_ArmNotification_t armMode;
} ZCL_ACEResponseArm_t;

//ByPass Command
typedef struct PACK
{
  uint16_t  getZoneIdMapResponse[ZCL_IAS_ACE_MAP_ID_RESPONSE_SIZE];
} ZCL_GetZoneIdMapResponse_t;

//ZoneId Information Commands
typedef struct PACK
{
  uint8_t  zoneId;
} ZCL_GetZoneInformationCommand_t;

typedef struct PACK
{
  uint8_t  zoneId;
  uint16_t zoneType;
  uint64_t zoneAddress;
  uint8_t length;
  uint8_t  zoneLabel[ZCL_IAS_ACE_ZONE_LABEL_SIZE];
} ZCL_GetZoneInformationResp_t;

typedef struct PACK
{
  uint8_t zoneId;
  uint8_t armDisarmCode[ZCL_IAS_ACE_ARM_DISARM_CODE_SIZE];
}bypassList_t;

//Panel Status Commands
typedef struct PACK
{
  ZCL_PanelStatus_t panel_status;
  uint8_t seconds_remaining;
} ZCL_AcePanelStatusChangeCommand_t;

typedef struct PACK
{
 ZCL_PanelStatus_t panel_status;
 uint8_t seconds_remain;
 ZCL_AudibleNotification_t audible_noti;
 ZCL_AlarmStatus_t alarmstatus; 
}ZCL_ACEGetPanelStatusCommandResp_t;

//GetZone Status Commands
typedef struct PACK
{
  uint8_t starting_zone_id;
  uint8_t max_number_zoneids;
  uint8_t zonestatus_maskflag;
  uint16_t zonestatus_mask; 
}ZCL_ACEGetZoneStatusCommand_t;

//Get Panel Status Commands
typedef struct PACK
{
  ZCL_PanelStatus_t panel_status;
  uint8_t seconds_remaining;
  ZCL_AudibleNotification_t audible_noti;
  ZCL_AlarmStatus_t alarmstatus;   
}ZCL_ACEPanelStatusChangedCommand_t;

//Get Zone CHANGED Command
typedef struct PACK
{
  uint8_t zoneid;
  uint16_t zoneStatus;
  ZCL_AudibleNotification_t audible_noti;
  uint8_t zoneLength;
  uint8_t zoneLabel[ZCL_IAS_ACE_ZONE_LABEL_SIZE];
}ZCL_ACEZoneStatusChangedCommand_t;

END_PACK

// IAS ACE Cluster Commands
typedef struct
{
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceArmCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEArm_t *payload);
  } aceArmCommand;
  
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceArmResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEResponseArm_t *payload);
  } aceArmResponseCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceByPassCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceByPassCommand;  
  
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceEmergencyCommand)(ZCL_Addressing_t *addressing);
  } aceEmergencyCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceFireCommand)(ZCL_Addressing_t *addressing);
  } aceFireCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*acePanicCommand)(ZCL_Addressing_t *addressing);
  } acePanicCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceGetZoneIdMapCommand)(ZCL_Addressing_t *addressing);
  } aceGetZoneIdMapCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneIdMapResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneIdMapResponse_t *payload);
  } aceGetZoneIdMapResponseCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*aceGetZoneInformationCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationCommand_t *payload);
  } aceGetZoneInformationCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneInformationResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetZoneInformationResp_t *payload);
  } aceGetZoneInformationResponseCommand;
  
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetPanelStatusCommand)(ZCL_Addressing_t *addressing);
  } aceGetPanelStatusCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetPanelStatusCommandResp)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetPanelStatusCommandResp_t *payload);
  } aceGetPanelStatusCommandResp;  

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneStatusCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEGetZoneStatusCommand_t *payload);
  } aceGetZoneStatusCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetZoneStatusRespCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceGetZoneStatusRespCommand; 

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*acePanelStatusChangedCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEPanelStatusChangedCommand_t *payload);
  } acePanelStatusChangedCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceZoneStatusChangedCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ACEZoneStatusChangedCommand_t *payload);
  } aceZoneStatusChangedCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceGetByPassedZoneListCommand)(ZCL_Addressing_t *addressing);
  } aceGetByPassedZoneListCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceSetByPassesZoneListCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceSetByPassesZoneListCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*aceByPassResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
  } aceByPassResponseCommand;
} ZCL_IasACEClusterCommands_t;
#endif /* _ZCLIASZONECLUSTER_H_ */
