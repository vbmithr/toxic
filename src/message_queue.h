/*  message_queue.h
 *
 *  Copyright (C) 2014-2024 Toxic All Rights Reserved.
 *
 *  This file is part of Toxic. Toxic is free software licensed
 *  under the GNU General Public License 3.0.
 */

#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

struct cqueue_msg {
    char message[MAX_STR_SIZE];
    size_t len;
    int line_id;
    time_t last_send_try;
    time_t time_added;
    uint8_t type;
    int64_t receipt;
    bool noread_flag;
    struct cqueue_msg *next;
    struct cqueue_msg *prev;
};

struct chat_queue {
    struct cqueue_msg *root;
    struct cqueue_msg *end;
};

void cqueue_cleanup(struct chat_queue *q);
void cqueue_add(struct chat_queue *q, const char *msg, size_t len, uint8_t type, int line_id);

/*
 * Tries to send all messages in the send queue in sequential order.
 * If a message fails to send the function will immediately return.
 */
void cqueue_try_send(ToxWindow *self, Tox *tox);

/*
 * Sets the noread flag for messages sent to the peer associated with `self` which have not
 * received a receipt after a period of time.
 */
void cqueue_check_unread(ToxWindow *self);

/* removes message with matching receipt from queue, writes to log and updates line to show the message was received. */
void cqueue_remove(ToxWindow *self, Toxic *toxic, uint32_t receipt);

#endif /* MESSAGE_QUEUE_H */
