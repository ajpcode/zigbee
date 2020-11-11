#ifndef UBEE__ASPDE__H
#define UBEE__ASPDE__H

#include <stdint.h>

struct address {
    /**
     * FIXME: I've just made this up!!
     */
    uint16_t address;
};


struct apsde_request {
    /**
     * The addressing mode for the destination address used in this primitive
     * and of the APDU to be transferred. This parameter can take one of the
     * non-reserved values from the following list:
     *   0x00 = DstAddress and DstEndpoint not present
     *   0x01 = 16-bit group address for DstAddress; DstEndpoint not present
     *   0x02 = 16-bit address for DstAddress and DstEndpoint present
     *   0x03 = 64-bit extended address for DstAddress and DstEnd-point present
     *   0x04 – 0xff = reserved
     */
    uint8_t dst_addr_mode;
    /**
     * The individual device address or group address of the entity to which
     * the ASDU is being transferred.
     * 
     * Valid range 0x0 - 0xff
     */
    struct address dst_addr;
    /**
     * This parameter shall be present if, and only if, the DstAddr-Mode
     * parameter has a value of 0x02 or 0x03 and, if present, shall be either
     * the number of the individual endpoint of the entity to which the ASDU is
     * being transferred or the broadcast endpoint (0xff).
     */
    uint8_t dst_endpoint;
    /**
     * The identifier of the profile for which this frame is intended.
     * 
     * Valid range 0x0 - 0xffff
     */
    uint16_t profile_id;
    /**
     * The identifier of the object for which this frame is intended.
     * 
     * Valid range 0x0 - 0xffff
     */
    uint16_t cluster_id;
    /**
     * The individual endpoint of the entity from which the ASDU is being
     * transferred.
     * 
     * Valid range 0x0 - 0xfe
     */
    uint8_t src_endpoint;
    /**
     * The number of octets comprising the ASDU to be transferred. The maximum
     * length of an individual APS frame payload is given as 
     * NsduLength - apscMinHeaderOverhead. 
     * 
     * Assuming fragmentation is used, there can be 256 such blocks comprising a single maximum sized ASDU.
     * 
     * 0x0 - 0xbf4
     */
    uint16_t asdu_length;
    
    /**
     * The set of octets comprising the ASDU to be transferred.
     */
    uint8_t* asdu;

    /**
     * The transmission options for the ASDU to be transferred. 
     * 
     * These are a bitwise OR of one or more of the following:
     *   0x01 = Security enabled transmission
     *   0x02 = Use NWK key
     *   0x04 = Acknowledged transmission
     *   0x08 = Fragmentation permitted
     *   0x10 = Include extended nonce in APS security frame. 
     */
    uint8_t tx_options;

    /**
     * The next higher layer may use the UseAlias parameter to re-quest alias
     * usage by NWK layer for the current frame. 
     * 
     * If the UseAlias parameter has a value of FALSE, meaning no alias usage,
     * then the parameters AliasSrcAddr and AliasSeqNumb will be ignored.
     * 
     * Otherwise, a value of TRUE denotes that the values supplied in
     * AliasSrcAddr and AliasSeqNumb are to be used.
     */
    bool use_alias;

    /**
     * The source address to be used for this NSDU.
     * 
     * If the UseAlias parameter has a value of FALSE, the AliasSrcAddr
     * parameter is ignored.
     */
    uint16_t alias_src_address;

    /**
     * The sequence number to be used for this NSDU. 
     * 
     * If the UseAlias parameter has a value of FALSE, the AliasSeqNumb
     * parameter is ignored.
     * 
     * Valid range: 0x0 0xff
     */
    uint8_t alias_seq_number;

    /**
     * The distance, in hops, that a transmitted frame will be allowed to
     * travel through the network.
     * 
     * Valid range: 0x0 - 0xff
     */
    uint8_t radius;
};


enum apsde_confirm_status {
    SUCCESS,
    SUCCESS, 
    NO_SHORT_ADDRESS, 
    NO_BOUND_DEVICE, 
    SECURITY_FAIL,
    NO_ACK,
    ASDU_TOO_LONG
};



/**
 * The primitive reports the results of a request to transfer a data PDU (ASDU)
 * from a local NHLE to one or 1496 more peer NHLEs.
 */
struct apsde_confirm {
    /**
     * The addressing mode for the destination address used in this primitive
     * and of the APDU to be transferred.
     * 
     * This parameter can take one of the non-reserved values from the
     * following list:
     *   0x00 = DstAddress and DstEndpoint not present
     *   0x01 = 16-bit group address for DstAddress; DstEndpoint not present
     *   0x02 = 16-bit address for DstAddress and DstEndpoint present
     *   0x03= 64-bit extended address for DstAddress and DstEndpoint present
     *   0x04 – 0xff = reserved
     */
    uint8_t dst_address_mode;  

    /**
     * The individual device address or group address of the entity to which
     * the ASDU is being transferred.
     */
    struct address dst_address;

    /**
     * This parameter shall be present if, and only if, the DstAddrMode
     * parameter has a value of 0x02 or 0x03 and, if present, shall be the
     * number of the individual endpoint of the entity to which the ASDU is
     * being transferred.
     * 
     * Valid range: 0x0 - 0xff
     */
    uint8_t dst_endpoint;

    /**
     * The individual endpoint of the entity from which the ASDU is being
     * transferred.
     * 
     * Valid range: 0x0 - 0xfe
     */
    uint8_t src_endpoint;

    /**
     * The status of the corresponding request.
     */
    enum apsde_confirm_status status;

    /**
     * A time indication for the transmitted packet based on the local clock,
     * as provided by the NWK layer.
     * 
     * TODO: Verify this type!
     */
    uint32_t tx_time;
};

enum apsde_indication_status {
    SUCCESS,
    DEFRAG_UNSUPPORTED,
    DEFRAG_DEFERRED,
};

enum apsde_decurity_status {
    UNSECURED,
    SECURED_NWK_KEY,
    SECURED_LINK_KEY
};

struct apsde_indication {
    /**
     * The addressing mode for the destination address used in this primitive
     * and of the APDU to be transferred.
     * 
     * This parameter can take one of the non-reserved values from the
     * following list:
     *   0x00 = DstAddress and DstEndpoint not present
     *   0x01 = 16-bit group address for DstAddress; DstEndpoint not present
     *   0x02 = 16-bit address for DstAddress and DstEndpoint present
     *   0x03= 64-bit extended address for DstAddress and DstEndpoint present
     *   0x04 – 0xff = reserved
     */
    uint8_t dst_address_mode;  

    /**
     * The individual device address or group address of the entity to which
     * the ASDU is being transferred.
     */
    struct address dst_address;

    /**
     * This parameter shall be present if, and only if, the DstAddrMode
     * parameter has a value of 0x02 or 0x03 and, if present, shall be the
     * number of the individual endpoint of the entity to which the ASDU is
     * being transferred.
     * 
     * Valid range: 0x0 - 0xff
     */
    uint8_t dst_endpoint;

    /**
     * The addressing mode for the source ad-dress used in this primitive and
     * of the APDU that has been received. 
     * 
     * This parameter can take one of the non-reserved values from the
     * following list:
     *   0x00 = reserved
     *   0x01 = reserved
     *   0x02 = 16-bit short address for SrcAddress and SrcEndpoint present
     *   0x03 = 64-bit extended address for SrcAddress and SrcEndpoint present
     *   0x04 = 64-bit extended address for SrcAddress, but SrcEndpoint NOT pre-sent.
     *   0x05 – 0xff = reserved
     */
    uint8_t src_address_mode;  

    /**
     * The number of the individual endpoint of the entity from which the ASDU
     * has been received.
     * 
     * Valid range: 0x0 - 0xfe
     */
    uint8_t src_endpoint;

    /**
     * The identifier of the profile from which this frame originated.
     * 
     * Valid range: 0x0 - 0xffff
     */
    uint16_t profile_id;

    /**
     * The identifier of the received object.
     * 
     * Valid range: 0x0 - 0xffff
     */
    uint16_t cluster_id;

    /**
     * The number of octets comprising the ASDU being indicated by the APSDE.
     */
    uint16_t asdu_length;

    /**
     * The set of octets comprising the ASDU being indicated by the APSDE.
     */
    uint8_t* asdu;


    /**
     * The status of the incoming frame pro-cessing.
     * 
     * Valid values: SUCCESS, DEFRAG_UNSUPPORTED, DEFRAG_DEFERRED or any
     *               status returned from the security pro-cessing of the frame
     */
    enum apsde_indication_status status;

    /**
     * UNSECURED if the ASDU was received without any security.
     * SECURED_NWK_KEY if the received ASDU was secured with the NWK key.
     * SECURED_LINK_KEY if the ASDU was secured with a link key.
     */
    enum apsde_decurity_status security_status;

    /**
     * The link quality indication delivered by the NLDE.
     * 
     * Valid range: 0x0 - 0xff
     */
    uint8_t link_quality;

    /**
     * A time indication for the received packet based on the local clock, as
     * provided by the NWK layer.
     * 
     * TODO: Validate the type of this variable!
     */
    uint32_t rx_time;
};

#endif