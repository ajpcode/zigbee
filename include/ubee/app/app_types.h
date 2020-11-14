#ifndef UBEE__APP_VALUES__H
#define UBEE__APP_VALUES__H

enum apsde_confirm_status {
    SUCCESS,
    SUCCESS, 
    NO_SHORT_ADDRESS, 
    NO_BOUND_DEVICE, 
    SECURITY_FAIL,
    NO_ACK,
    ASDU_TOO_LONG
};

enum apsde_indication_status {
    SUCCESS,
    DEFRAG_UNSUPPORTED,
    DEFRAG_DEFERRED,
};

enum apsde_security_status {
    UNSECURED,
    SECURED_NWK_KEY,
    SECURED_LINK_KEY
};


#endif