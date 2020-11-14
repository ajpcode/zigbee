#ifndef UBEE__NET__H
#define UBEE__NET__H

#include <stdint.h>

#include "nwk_types.h"

/**
 * ----------------------------------------------------------------------------
 * Functions for controllers (/distributed security?)
 * ----------------------------------------------------------------------------
 */

/**
 * Network formation function.
 * TBC: parameter list
 */
nwk_result_t nwk_create( nwk_params_t parameters );


/**
 * This fuction allows the next higher layer to request that the NWK layer
 * discover networks currently operating within the local area.
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
nwk_result_t nwk_scan_start( uint32_t scan_channels, uint8_t scan_duration );

/**
 * This function allows the next higher layer request that thw NWK layer
 * terminate any currently running scan operation as soon as possible and not
 * return any further results.
 */
nwk_result_t nwk_scan_stop( void );
/**
 * Callback to handle responses to discovery request.
 */
nwk_result_t nwk_scan_cb( nwk_params_t nwk_parameters );


/**
 * ----------------------------------------------------------------------------
 * Allows a currently unadoped device to attempt to join a network.
 * ----------------------------------------------------------------------------
 */

/**
 * 
 */
nwk_result_t nwk_join( nwk_node_type_t node_type, nwk_params_t parameters );
/**
 * 
 */
nwk_result_t nwk_rejoin( nwk_node_type_t node_type, nwk_params_t parameters );
/**
 * 
 */
nwk_result_t nwk_leave( void );

/**
 * ----------------------------------------------------------------------------
 * Already adopted to a network/controller devices
 * ----------------------------------------------------------------------------
 */
nwk_result_t nwk_permit_joining( uint8_t duration );


/**
 * 
 */
nwk_result_t nwk_reset( void );




#endif