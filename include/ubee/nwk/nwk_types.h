#ifndef UBEE__NET_STRUCTS__H
#define UBEE__NET_STRUCTS__H

#include <stdint.h>

#include "versions.h"
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

/**
 * These status codes are used both as values for the status code field of a network status command frame and as values of the Status parameter of the NLME-NWK-STATUS.indication primitive. A brief explanation of each follows: 
 */
typedef enum nwk_status_e {
    /**
     * Route discovery and/or repair has been attempted and no route to the intended destination address has been discovered.
     */
    NO_ROUTE_AVAILABLE = 0x0,
    /**
     * The routing failure occurred as a result of the failure of an attempt to route the frame along the tree.
     */
    TREE_LINK_FALURE = 0x1,
    /**
     * The routing failure did not occur as a result of an attempt to route along the tree.
     */
    NON_TREE_LINK_FALURE = 0x2,
    /**
     * The frame was not relayed because the relaying device was running low on battery power.
     */
    LOW_BATTERY_LEVEL = 0x3,
    /**
     * The failure occurred because the relaying device has no routing capacity.
     */
    NO_ROUTING_CAPACITY = 0x4,
    /**
     * The failure occurred as the result of an attempt to buffer a frame for a sleeping 7296 end device child and the relaying device had no buffer capacity to use.
     */
    NO_INDIRECT_CAPACITY = 0x5,
    /**
     * A frame that was buffered on behalf of a sleeping end device child has been dropped as a result of a time-out.
     */
    INDIRECT_TRANSACTION_EXPIRY = 0x6,
    /**
     * An end device child of the relaying device is for some reason unavailable.
     */
    TARGET_DEVICE_UNAVAILABLE = 0x7,
    /**
     * The frame was addressed to a non-existent end device child of the relaying device.
     */
    TARGET_ADDRESS_UNALLOCATED = 0x8,
    /**
     * The failure occurred as a result of a failure in the RF link to the device’s parent. This status is only used locally on a device to indicate loss of communication with the parent.
     */
    PARENT_LINK_FAILURE = 0x9,
    /**
     * The multicast route identified in the destination address field should be validated as described in section 3.6.3.6. 
     */
    VALIDATE_ROUTE = 0xa,
    /**
     * Source routing has failed, probably indicating a link failure in one of the source route’s links.
     */
    SOURCE_ROUTE_FAILURE = 0xb,
    /**
     * A route established as a result of a many-to-one route request has failed.
     */
    MANY_TO_ONE_ROUTE_FAILURE = 0xc,
    /**
     * The address in the destination address field has been determined to be in use by two or more devices.
     */
    ADDRESS_CONFLICT = 0xd,
    /**
     * The source device has the IEEE address in the Source IEEE address field and, if the Destination IEEE address field is present, the value it contains is the expected IEEE address of the destination.
     */
    VERIFY_ADDRESS = 0xe,
    /**
     * The operational network PAN identifier of the device has been updated.
     */
    PAN_IDENTIFIER_UPDATE = 0xf,
    /**
     * The network address of the device has been updated.
     */
    NETWORK_ADDRESS_UPDATE = 0x10,
    /**
     * A frame counter reported in a received frame had a value less than or equal to that stored in nwkSecurityMaterialSet. 
     */
    BAD_FRAME_COUNTER = 0x11,
    /**
     * The key sequence number reported in a received frame did not match that of nwkActiveKeySeqNumber.
     */
    BAD_KEY_SEQUENCE_NUMBER = 0x12
} nwk_status_t;

typedef enum nwk_discovery_status_e {
    SUCCESS,
    INVALID_REQUEST,
    ROUTE_ERROR,
} nwk_discovery_status_t;

typedef enum nwk_node_type_e {
    UNKNOWN,
    COORDINATOR,
    ROUTER,
    END_DEVICE,
    LE_END_DEVICE
} nwk_node_type_t;



typedef struct nwk_params_s {
    /**
     * The 64-bit PAN identifier of the network.
     * 
     * Valid range: 0x1 - 0xfffffffffffffffe
     */
    uint64_t extended_pan_id;

    /**
     * Selected from the available logical channels supported by the PHY.
     */
    uint32_t logical_channels;

    /**
     * A ZigBee stack profile identifier indicating the stack profile in use in
     * the discovered network.
     * 
     * Valid range: 0x0 - 0xf
     */
    uint8_t stack_profile;

    /**
     * The version of the ZigBee protocol in use in the dis-covered network.
     * 
     * Valid range: 0x0-0xf
     */
    uint8_t zigbee_version;

    /**
     * This specifies how often the MAC sub-layer beacon is to be transmitted
     * by a given device on the network.
     * 
     * Valid range: 0x0-0xf
     */
    uint8_t beacon_order;

    /**
     * For beacon-oriented net-works, that is, beacon order < 15, this
     * specifies the length of the active period of the superframe.
     * 
     * Valid range: 0x0-0xf
     */
    uint8_t superframe_order;
} nwk_params_t;

enum nwk_discovery_status {
    STARTED,
    ALREADY_RUNNING,
    INVALID_REQUEST,
    ROUTE_ERROR,
};


typedef enum nwk_result_e {
    SUCCESS,
    FAILED, // ... everything else ...
} nwk_result_t;


typedef struct nwk_discovery_result_s {
    /**
     * The status of an attempt to initiate route discovery.
     */
    nwk_discovery_status_t status;
    
    /**
     * In the case where the Status parameter has a value of ROUTE_ERROR, this
     * code gives further information about the kind of error that occurred.
     * Otherwise, it should be ignored.
     */
    nwk_status_t code;

} nwk_discovery_result_t;


#endif