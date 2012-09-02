#include "redis.h"

bintreeNode *bintreeInsert(bintree *tree, double value, robj *member) {
    bintreeNode *node = zmalloc(sizeof(*node));

    node->value = value;
    node->obj = member;

    return node;
    /* TODO: insert node into tree, set left and right pointers */
}

void bsetCommand(redisClient *c) {
    robj *key = c->argv[1];
    robj *binobj;
    robj *member;
    bintree *tree;
    bintreeNode *node;
    double value=0;

    if (c->argc != 4) {
        addReply(c,shared.syntaxerr);
        return;
    }

    if (getDoubleFromObjectOrReply(c,c->argv[2],&value,NULL) != REDIS_OK) {
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

    tree = (bintree*)binobj->ptr;
    member = tryObjectEncoding(c->argv[3]);
    node = bintreeInsert(tree,value,member);

    addReplyLongLong(c,1);
}
