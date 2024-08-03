#ifndef AT42QT1070_H_
#define AT42QT1070_H_

#include <stdint.h>
#include <stdbool.h>
#include "status.h"

#define AT42QT1070_ADDR 0x1B

#define AT42QT_KEY_STATUS_0 (1<<0)
#define AT42QT_KEY_STATUS_1 (1<<1)
#define AT42QT_KEY_STATUS_2 (1<<2)
#define AT42QT_KEY_STATUS_3 (1<<3)
#define AT42QT_KEY_STATUS_4 (1<<4)
#define AT42QT_KEY_STATUS_5 (1<<5)
#define AT42QT_KEY_STATUS_6 (1<<6)

#define AT42QT_LP_INTERVAL 8U //ms
#define AT42QT_MAX_ON_INTERVAL 160U //ms

typedef union {
    struct {
        uint8_t calibrate: 1;
        uint8_t overflow: 1;
        uint8_t rsvd: 5;
        uint8_t touch: 1;
    };
    uint8_t byte;
} at42qt_status_t;

typedef enum {
    AT42QT_KEY_0 = 0,
    AT42QT_KEY_1,
    AT42QT_KEY_2,
    AT42QT_KEY_3,
    AT42QT_KEY_4,
    AT42QT_KEY_5,
    AT42QT_KEY_6,
    AT42QT_KEY_NONE,
} at42qt_key_t;

typedef enum {
    AT42QT_AVE_1 = 1,
    AT42QT_AVE_2 = 2,
    AT42QT_AVE_4 = 4,
    AT42QT_AVE_8 = 8,
    AT42QT_AVE_16 = 16,
    AT42QT_AVE_32 = 32,
} at42qt_avg_factor_t;

typedef enum {
    AT42QT_SUPP_GROUP_NONE = 0,
    AT42QT_SUPP_GROUP_1 = 1,
    AT42QT_SUPP_GROUP_2 = 2,
    AT42QT_SUPP_GROUP_3 = 3,
} at42qt_supp_group_t;

status_t at42qt_get_chipid(uint8_t *major, uint8_t *minor);
status_t at42qt_get_fwversion(uint8_t *version);
status_t at42qt_get_status(at42qt_status_t *det_status);
status_t at42qt_get_key_status(uint8_t *key_status);

status_t at42qt_get_key_signal(at42qt_key_t key, uint16_t *signal);
status_t at42qt_get_ref_data(at42qt_key_t key, uint16_t *data);

status_t at42qt_set_neg_thresh(at42qt_key_t key, uint8_t thresh);
status_t at42qt_get_neg_thresh(at42qt_key_t key, uint8_t *thresh);

status_t at42qt_set_avg_factor(at42qt_key_t key, at42qt_avg_factor_t factor);
status_t at42qt_get_avg_factor(at42qt_key_t key, at42qt_avg_factor_t *factor);

status_t at42qt_set_key_suppression_group(at42qt_key_t key, at42qt_supp_group_t group);
status_t at42qt_get_key_suppression_group(at42qt_key_t key, at42qt_supp_group_t *group);

status_t at42qt_set_det_integrator(at42qt_key_t key, uint8_t integrator);
status_t at42qt_get_det_integrator(at42qt_key_t key, uint8_t *integrator);

status_t at42q_set_fastout(bool fastout);
status_t at42q_get_fastout(bool *fastout);

status_t at42q_set_maxcal(bool maxcal);
status_t at42q_get_maxcal(bool *maxcal);

status_t at42q_set_guardchan(at42qt_key_t key);
status_t at42q_get_guardchan(at42qt_key_t *key);

status_t at42q_set_lpmode(uint8_t intervals);
status_t at42q_get_lpmode(uint8_t *intervals);

status_t at42q_set_maxon(uint8_t intervals);
status_t at42q_get_maxon(uint8_t *intervals);

status_t at42q_calibrate(void);
status_t at42q_reset(void);

#endif