#include "redis.h"

void bsetCommand(redisClient *c) {
    robj *key = c->argv[1];

    if (c->argc != 4) {
        addReply(c,shared.syntaxerr);
        return;
    }

    addReply(c,shared.ok);
}
