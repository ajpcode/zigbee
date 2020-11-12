#ifndef UBEE__NET_STRUCTS__H
#define UBEE__NET_STRUCTS__H

#include <stdint.h>

#include "net_values.h"

struct net_info {
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
};

enum net_discovery_status {
    OK,
    INVALID_REQUEST,
    ROUTE_ERROR,
};

typedef struct net_discovery_result_s {
    /**
     * The status of an attempt to ini-tiate route discovery.
     */
    net_discovery_status status;
    /**
     * In the case where the Status parameter has a value of ROUTE_ERROR, this
     * code gives further information about the kind of error that occurred.
     * Otherwise, it should be ignored.
     */
    net_status_code code;
} net_discovery_result_t;

#endif