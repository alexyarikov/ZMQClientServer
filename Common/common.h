#ifndef COMMON_H_
#define COMMON_H_

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <zmq.h>

#include "message_data.h"
#include "tools.h"

#include "Data/insert_req.pb-c.h"
#include "Data/insert_res.pb-c.h"
#include "Data/delete_req.pb-c.h"
#include "Data/delete_res.pb-c.h"
#include "Data/query_by_id_req.pb-c.h"
#include "Data/query_by_id_res.pb-c.h"
#include "Data/query_by_compensation_range_req.pb-c.h"
#include "Data/query_by_compensation_range_res.pb-c.h"

#endif /* COMMON_H_ */
