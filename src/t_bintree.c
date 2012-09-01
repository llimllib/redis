#include "redis.h"

void bsetCommand(redisClient *c) {
    robj *key = c->argv[1];
    double score=0;

    if (c->argc != 4) {
        addReply(c,shared.syntaxerr);
        return;
    }

    if (getDoubleFromObjectOrReply(c,c->argv[2],&score,NULL) != REDIS_OK) {
        return;
    }

    addReply(c,shared.ok);
}
