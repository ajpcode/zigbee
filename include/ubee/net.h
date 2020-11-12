#ifndef UBEE__NET__H
#define UBEE__NET__H

#include <stdint.h>

#include "net_values.h"
#include "net_structs.h"


/**
 * This primitive allows the next higher layer to request that the NWK layer
 * discover networks currently operating within the POS.
 * 
 * scan_channels : 
 *   The five most significant bits (b27,..., b31) are reserved. The 27 least
 *   significant bits (b0, b1,... b26) indicate which channels are to be
 *   scanned (1 = scan, 0 = do not scan) for each of the 27 validchannels 
 *   (see [B1]). 
 *   [0x0-7FFFFFF]
 * 
 * scan_duration : 
 *   A value used to calculate the length of time to spend scanning each
 *   channel:
 *   The time spent scanning each channel is...
 *     (aBaseSuperframeDuration* (2n + 1)) 
 *   ... symbols, where n is the value of the ScanDuration parameter.
 *   For more information on MAC sub-layer scanning (see [B1]). 
 *   [0x0-0xe]
 */
net_discovery_result_t net_discovery( uint32_t scan_channels, uint8_t scan_duration );



#endif