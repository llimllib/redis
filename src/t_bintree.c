#include "redis.h"

void bsetCommand(redisClient *c) {
    addReply(c, shared.ok);
}
