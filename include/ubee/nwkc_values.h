#ifndef UBEE__NWCK_VALUES__H
#define UBEE__NWCK_VALUES__H

#include <stdint.h>
#include <stdbool.h>

#include "zigbee_version.h"
#include "default_conf.h"

/**
 * A Boolean flag indicating whether the device is capable of becoming the
 * ZigBee coordinator.
 * 
 * A value of 0x00 indicates that the device is not capable of becoming a
 * coordinator while a value of 0x01 indicates that the device is capable of
 * becoming a coordinator. 
 * 
 * Configuration de-pendent.
 */
const bool nwkcCoordinatorCapable = CONFIG_UBEE_NETWORK_COORDINATOR;  

/**
 * The security level for out-going and incoming NWK frames; the allowable
 * security level identifiers are pre-sented in specification Table 4.40.
 * 
 * Valid range 0x0 - 0x7. 
 */
const uint8_t nwkcDefaultSecurityLevel = CONFIG_UBEE_SECURITY_LEVEL;

/**
 * The default security level to be used (see Chapter 4 of the 2015 ZigBee PrRo specification document). 
 * 
 * Defined in stack pro-file 
//const uint8_t nwkcDefaultSecurityLevel; // 

/**
 * The minimum number of octets added by the NWK layer to an NSDU. 
 */
const uint8_t  nwkcMinHeaderOverhead    = 0x08;

/**
 * The version of the ZigBee NWK protocol in the device.
 */
const uint8_t  nwkcProtocolVersion      = zigbee_version_pro;

/**
 * The number of OctetDurations, on the originator of a multicast route
 * request, between receiving a route reply and sending a message to validate
 * the route. 0x9c40 (0x500 msec on 2.4 GHz)
 */
const uint16_t nwkcWaitBeforeValidation = 0x9c40; 

/**
 * The size of the MAC header used by the ZigBee NWK layer.
 */
const uint8_t  nwkcMACFrameOverhead     = 0x0b;



#endif