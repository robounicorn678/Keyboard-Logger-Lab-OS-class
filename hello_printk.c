/** hello_printk.c
 *  ===========================================================
 *  Name:    CS483
 *  Section: CS 483 — Operating Systems
 *  Project: Keyboard Logger Lab (PEX) — starter module
 *  Purpose: Minimal loadable Linux kernel module. On insmod
 *           the kernel calls moduleInit(); on rmmod it calls
 *           moduleExit(). Both write to the kernel log via
 *           pr_info(), which students view with dmesg.
 *
 *           Students extend this file by splicing the notifier
 *           callback and notifier_block from keyboard.c into
 *           this file to turn it into a working keylogger.
 *  ===========================================================
 */

/* Kernel headers (no user-space C system headers are allowed
 * in a kernel module — the kernel provides its own.)            */
#include <linux/init.h>      /* __init, __exit markers          */
#include <linux/module.h>    /* module_init, module_exit, MODULE_* */
#include <linux/printk.h>    /* pr_info                          */

/**
 * @brief  Module load entry point.
 * @return 0 on success; a nonzero return aborts the load.
 *
 * Called exactly once by the kernel when the module is
 * inserted via insmod. Announces a load banner to the kernel
 * log so the student can confirm the load with dmesg.
 */
static int __init moduleInit(void) {
    pr_info("CS483 Keylogger: module loaded.\n");
    return 0;
}

/**
 * @brief Module unload entry point.
 *
 * Called exactly once by the kernel when the module is
 * removed via rmmod. Announces an unload banner to the kernel
 * log so the student can confirm a clean unload with dmesg.
 */
static void __exit moduleExit(void) {
    pr_info("CS483 Keylogger: module unloaded.\n");
}

/* Register the entry / exit points with the kernel module loader. */
module_init(moduleInit);
module_exit(moduleExit);

/* Module metadata read by the kernel and `modinfo`. Do not change
 * the license — "GPL" grants us access to GPL-only kernel symbols
 * (including the keyboard notifier API used in the next step).    */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS483");
MODULE_DESCRIPTION("CS483 PEX: Keyboard Logger starter module");
MODULE_VERSION("1.0");