#include "redis.h"

void bsetCommand(redisClient *c) {
    robj *key = c->argv[1];
    robj *binobj;
    double score=0;

    if (c->argc != 4) {
        addReply(c,shared.syntaxerr);
        return;
    }

    if (getDoubleFromObjectOrReply(c,c->argv[2],&score,NULL) != REDIS_OK) {
        return;
    }

    binobj = lookupKeyWrite(c->db,key);
    if (binobj == NULL) {
        binobj = createBintreeObject();
        dbAdd(c->db,key,binobj);
    } else {
        if (binobj->type != REDIS_BINTREE) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }

    addReply(c,shared.ok);
}
